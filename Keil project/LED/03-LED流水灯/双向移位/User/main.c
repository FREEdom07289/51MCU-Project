/**
 * @file    main.c
 * @brief   LED 实验 03（方案 C）：读回端口 + 循环移位库函数实现流水灯
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    硬件：STC89C52 + 8 位 LED（P2.0 ~ P2.7，低电平点亮）
 *          现象：亮点从 D1 移到 D8，再原路返回，循环往复，每步 500ms
 *          修改记录：
 *            V1.0 2026-11-14 按模块化规范重组，P2 口操作移入 Driver/LED.c
 */
#include <REGX52.H>
#include <INTRINS.H>
#include "LED.h"
#include "Delay.h"

/* ==================== 宏定义 ==================== */

#define LED_START_PATTERN   0xFE    /* 起始图案：仅 bit0 为低电平，即 D1 点亮 */
#define LED_SHIFT_TIMES     7       /* D1 移到 D8 共 7 步，第 8 步会回到起点 */
#define LED_STEP_US         50000   /* 每步停留 50000 × 10us，约 500ms */

/* ==================== 主函数 ==================== */

void main(void)
{
    unsigned char i;            /* 移位步数计数器 */

    LED_Init();
    LED_WriteAll(LED_START_PATTERN);
    Delay_10us(LED_STEP_US);    /* 先在 D1 上停留一步，与原实验保持一致 */

    while (1)
    {
        /* 正向：D1 → D8 */
        for (i = 0; i < LED_SHIFT_TIMES; i++)
        {
            LED_WriteAll(_crol_(LED_ReadAll(), 1));    /* 读回当前图案整体左移一位 */
            Delay_10us(LED_STEP_US);
        }

        /* 反向：D8 → D1 */
        for (i = 0; i < LED_SHIFT_TIMES; i++)
        {
            LED_WriteAll(_cror_(LED_ReadAll(), 1));    /* 读回当前图案整体右移一位 */
            Delay_10us(LED_STEP_US);
        }
    }
}

