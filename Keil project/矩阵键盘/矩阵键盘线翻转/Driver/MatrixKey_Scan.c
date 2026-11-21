/**
 * @file    MatrixKey_Scan.c
 * @brief   4×4 矩阵键盘驱动（线翻转法），两次翻转分别读出列号和行号
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-22
 * @note    硬件引脚（普中 A2 开发板）：
 *            P1.3 ~ P1.0 为列线，P1.7 ~ P1.4 为行线；
 *          线翻转法不逐列扫描，而是：
 *            ① 行线输出 0、列线作输入 → 读回被拉低的列（列号）
 *            ② 列线输出 0、行线作输入 → 读回被拉低的行（行号）
 *          键号 = 行 × 4 + 列 + 1
 *          依赖模块：Delay.c（提供 10ms 消抖延时）
 *          修改记录：
 *            V1.0 2026-11-22 新建，用两次翻转替代逐列扫描，接口与逐列版完全一致
 */

#include <REGX52.H>
#include "MatrixKey_Scan.h"
#include "Delay.h"

/* ==================== 私有宏与变量 ==================== */

#define KEYPAD_DEBOUNCE_MS  10      /* 按键消抖延时，单位 ms */
#define KEYPAD_COL_NUM      4       /* 列数 */

/* ==================== 私有函数声明 ==================== */

static unsigned char KeyPad_ReadCol(void);
static unsigned char KeyPad_ReadRow(void);
static unsigned char KeyPad_ColToIndex(unsigned char ColState);
static unsigned char KeyPad_RowToIndex(unsigned char RowState);

/* ==================== 对外接口实现 ==================== */

/**
 * @brief  扫描一次矩阵键盘，返回当前按下的键号
 * @retval 1 ~ 16：当前按下的键号（S1 ~ S16）；0：没有按键按下
 * @note   两次翻转必须针对同一个键：
 *           第一次“行低读列”确定列，第二次“列低读行”确定行；
 *         若两次之间手指松开，第二次读不到低电平，本次返回 0；
 *         按住不放会持续返回同一个键号，松开后返回 0
 */
unsigned char MatrixKey_Scan(void)
{
    unsigned char ColState;
    unsigned char RowState;
    unsigned char Col;
    unsigned char Row;

    /* ① 行线输出 0（P1.7~P1.4），列线弱上拉作输入（P1.3~P1.0） */
    KEYPAD_PORT = 0x0F;
    ColState = KeyPad_ReadCol();

    if (ColState == KEYPAD_COL_MASK)        /* 0x0F：没有列被拉低，本列/本轮无键 */
    {
        KEYPAD_PORT = 0xFF;
        return KEYPAD_NO_KEY;
    }

    Delay_ms(KEYPAD_DEBOUNCE_MS);           /* 等 10ms，让触点抖动过去 */
    ColState = KeyPad_ReadCol();

    if (ColState == KEYPAD_COL_MASK)        /* 10ms 后已经松开：是抖动 */
    {
        KEYPAD_PORT = 0xFF;
        return KEYPAD_NO_KEY;
    }

    Col = KeyPad_ColToIndex(ColState);      /* 列号 0 ~ 3 */

    /* ② 翻转：列线输出 0，行线弱上拉作输入 */
    KEYPAD_PORT = 0xF0;
    RowState = KeyPad_ReadRow();
    KEYPAD_PORT = 0xFF;                     /* 读完整即释放端口，避免长按持续导通 */

    if (RowState == KEYPAD_ROW_MASK)        /* 翻转后读不到行：两次之间松手了 */
    {
        return KEYPAD_NO_KEY;
    }

    Row = KeyPad_RowToIndex(RowState);      /* 行号 0 ~ 3 */
    return (unsigned char)(Row * KEYPAD_COL_NUM + Col + 1);
}

/* ==================== 私有函数实现 ==================== */

/**
 * @brief  读回列线状态
 * @retval bit3 ~ bit0 对应第 1 ~ 4 列，被按键拉低时为 0（0x0F 表示没有列被拉低）
 * @note   只在“行线输出 0”的阶段调用；此时高 4 位是自己输出的 0，不能参与判断
 */
static unsigned char KeyPad_ReadCol(void)
{
    return (unsigned char)(KEYPAD_PORT & KEYPAD_COL_MASK);
}

/**
 * @brief  读回行线状态
 * @retval bit7 ~ bit4 对应第 1 ~ 4 行，被按键拉低时为 0（0xF0 表示没有行被拉低）
 * @note   只在“列线输出 0”的阶段调用；此时低 4 位是自己输出的 0
 */
static unsigned char KeyPad_ReadRow(void)
{
    return (unsigned char)(KEYPAD_PORT & KEYPAD_ROW_MASK);
}

/**
 * @brief  把列线状态换算成列号
 * @param  ColState 列线读回值，取值 0x07 / 0x0B / 0x0D / 0x0E（多键时可能有多个 0）
 * @retval 列号 0 ~ 3，0 表示第 1 列（P1.3）
 * @note   从 P1.3 往 P1.0 找第一个为 0 的位；同一列多键不影响列号
 */
static unsigned char KeyPad_ColToIndex(unsigned char ColState)
{
    if ((ColState & 0x08) == 0)
    {
        return 0;                   /* P1.3 被拉低：第 1 列，S1/S5/S9/S13 */
    }
    if ((ColState & 0x04) == 0)
    {
        return 1;
    }
    if ((ColState & 0x02) == 0)
    {
        return 2;
    }
    return 3;                       /* P1.0：第 4 列，S4/S8/S12/S16 */
}

/**
 * @brief  把行线状态换算成行号
 * @param  RowState 行线读回值，取值 0x70 / 0xB0 / 0xD0 / 0xE0（多键时可能有多个 0）
 * @retval 行号 0 ~ 3，0 表示第 1 行（P1.7）
 * @note   从 P1.7 往 P1.4 找第一个为 0 的位
 */
static unsigned char KeyPad_RowToIndex(unsigned char RowState)
{
    if ((RowState & 0x80) == 0)
    {
        return 0;                   /* P1.7：第 1 行，S1 ~ S4 */
    }
    if ((RowState & 0x40) == 0)
    {
        return 1;
    }
    if ((RowState & 0x20) == 0)
    {
        return 2;
    }
    return 3;                       /* P1.4：第 4 行，S13 ~ S16 */
}