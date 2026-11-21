/**
 * @file    main.c
 * @brief   矩阵键盘实验：按下的按键点亮对应的 LED
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    硬件：STC89C52RC + 4×4 矩阵键盘（P1 口），按键 S1-S16
 *          功能：S1 ~ S8 按住时点亮 D1 ~ D8，松开后全部熄灭；
 *                S9 ~ S16 暂不参与控制
 *          扫描方式：线翻转法（行低读列 → 列低读行），接口与逐列扫描版相同
 *          硬件引脚：行线 P1.7~P1.4（第 1~4 行），列线 P1.3~P1.0（第 1~4 列）
 *          依赖模块：MatrixKey_Scan.c、LED.c、Delay.c
 *          修改记录：
 *            V1.0 2026-11-14 新建工程骨架
 *            V1.0 2026-11-14 实现扫描结果到单灯点亮的映射
 *            V1.1 2026-11-22 换用线翻转法扫描驱动，main 逻辑不变
 */
#include <REGX52.H>
#include "MatrixKey_Scan.h"
#include "LED.h"

/* ==================== 私有宏 ==================== */

#define KEY_LED_MAX     8       /* 只有 8 个 LED，S1 ~ S8 参与点亮 */

/* ==================== 主函数 ==================== */

void main(void)
{
    unsigned char KeyNum;

    LED_Init();                 /* 上电先全部熄灭 */

    while (1)
    {
        KeyNum = MatrixKey_Scan();      /* 无键返回 0，按住期间持续返回编号 */

        if ((KeyNum >= 1) && (KeyNum <= KEY_LED_MAX))
        {
            LED_OnOne(KeyNum - 1);      /* S1 ~ S8 对应 D1 ~ D8 */
        }
        else
        {
            LED_AllOff();               /* 无键或 S9 ~ S16 时熄灭全部 */
        }
    }
}
