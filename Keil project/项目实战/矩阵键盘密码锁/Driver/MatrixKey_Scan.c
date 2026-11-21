/**
 * @file    MatrixKey_Scan.c
 * @brief   4×4 矩阵键盘驱动（逐列扫描 + 软件消抖），返回当前按下的键号
 * @author  FREEDOM
 * @version V1.1
 * @date    2026-11-20
 * @note    硬件引脚（普中 A2 开发板）：
 *            P1.3 ~ P1.0 为列线（扫描时依次输出低电平），
 *            P1.7 ~ P1.4 为行线（读回，按下时对应行为低电平）
 *          依赖模块：Delay.c（提供 10ms 消抖延时）
 *          修改记录：
 *            V1.0 2026-11-14 新建工程骨架，扫描逻辑写到一半
 *            V1.1 2026-11-20 实现逐列扫描；去掉“等待松开”的阻塞，
 *                            改为按住期间持续返回键号，松开返回 0
 */

#include <REGX52.H>
#include "MatrixKey_Scan.h"
#include "Delay.h"

/* ==================== 私有宏与变量 ==================== */

#define KEYPAD_DEBOUNCE_MS  10      /* 按键消抖延时，单位 ms */
#define KEYPAD_COL_NUM      4       /* 列数 */

/* ==================== 私有函数声明 ==================== */

static unsigned char KeyPad_ReadRow(void);
static unsigned char KeyPad_RowToIndex(unsigned char RowState);

/* ==================== 对外接口实现 ==================== */

/**
 * @brief  扫描一次矩阵键盘，返回当前按下的键号
 * @retval 1 ~ 16：当前按下的键号（S1 ~ S16）；0：没有按键按下
 * @note   逐列把一根列线拉低，再读行线，哪一行为低就是哪一行的键；
 *         检测到按下后延时 10ms 再读一次，两次都为低才认定有效（消抖）；
 *         按住不放会持续返回同一个键号，松开后返回 0，调用者无需自己消抖；
 *         同一列同时按下两个键时只能识别靠上的一行（矩阵键盘的固有限制）
 */
unsigned char MatrixKey_Scan(void)
{
    unsigned char Col;
    unsigned char RowState;
    unsigned char KeyNum = KEYPAD_NO_KEY;

    for (Col = 0; Col < KEYPAD_COL_NUM; Col++)
    {
        KEYPAD_PORT = (unsigned char)~(0x08 >> Col);    /* 0xF7→0xFB→0xFD→0xFE，逐列拉低 P1.3→P1.0 */

        RowState = KeyPad_ReadRow();
        if (RowState == KEYPAD_ROW_MASK)                /* 0xF0：四行都是高，本列没键 */
        {
            continue;
        }

        Delay_ms(KEYPAD_DEBOUNCE_MS);                   /* 等 10ms，让抖动过去 */
        RowState = KeyPad_ReadRow();
        if (RowState == KEYPAD_ROW_MASK)                /* 10ms 后已松开：是抖动，不算按键 */
        {
            continue;
        }

        KeyNum = KeyPad_RowToIndex(RowState) * KEYPAD_COL_NUM + Col + 1;    /* 键号 = 行×4 + 列 + 1 */
        break;                                          /* 一次只报一个键，剩下的留给下一轮 */
    }

    KEYPAD_PORT = 0xFF;                                 /* 扫描结束把端口释放为高，避免长按持续导通 */
    return KeyNum;
}

/* ==================== 私有函数实现 ==================== */

/**
 * @brief  读回行线状态
 * @retval bit7 ~ bit4 对应第 1 ~ 4 行，按下时为 0，未按时为 1（0xF0 表示无键）
 * @note   只取高 4 位；低 4 位此刻是我们自己输出的列电平，不能拿来判断行列
 */
static unsigned char KeyPad_ReadRow(void)
{
    return (unsigned char)(KEYPAD_PORT & KEYPAD_ROW_MASK);
}

/**
 * @brief  把行线状态换算成行号
 * @param  RowState 行线读回值，取值 0x70 / 0xB0 / 0xD0 / 0xE0（多键时可能同时有多个 0）
 * @retval 行号 0 ~ 3，0 表示第 1 行
 * @note   从 P1.7 开始往下找第一个为 0 的位；找不到返回 3（调用前已排除 0xF0）
 */
static unsigned char KeyPad_RowToIndex(unsigned char RowState)
{
    if ((RowState & 0x80) == 0)
    {
        return 0;                   /* P1.7 被拉低：第 1 行，S1 ~ S4 */
    }
    if ((RowState & 0x40) == 0)
    {
        return 1;                   /* P1.6 被拉低：第 2 行，S5 ~ S8 */
    }
    if ((RowState & 0x20) == 0)
    {
        return 2;                   /* P1.5 被拉低：第 3 行，S9 ~ S12 */
    }
    return 3;                       /* 只剩 P1.4：第 4 行，S13 ~ S16 */
}