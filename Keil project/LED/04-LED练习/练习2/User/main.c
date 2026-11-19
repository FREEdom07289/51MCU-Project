/**
 * @file    main.c
 * @brief   LED 练习 02：双灯流水灯
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    硬件：STC89C52 + 8 位 LED（P2.0 ~ P2.7，低电平点亮）
 *          现象：D1、D2 同时点亮并逐位向高位移动，移满一轮后从头开始
 *          修改记录：
 *            V1.0 2026-11-14 按模块化规范重组，P2 口操作移入 Driver/LED.c
 */
#include <REGX52.H>
#include <INTRINS.H>
#include "LED.h"
#include "Delay.h"

/* ==================== 宏定义 ==================== */

#define LED_START_PATTERN   0xFC    /* 起始图案：bit0、bit1 为低电平，即 D1、D2 点亮 */
#define LED_SHIFT_TIMES     7       /* 移 7 步到达 D7、D8，第 8 步会破坏双灯模式 */
#define LED_STEP_MS         200     /* 每步停留时间，单位毫秒 */

/* ==================== 主函数 ==================== */

void main(void)
{
    unsigned char i;        /* 移位步数计数器 */

    LED_Init();

    while (1)
    {
        unsigned char Pattern = LED_START_PATTERN;   /* 每轮从双灯起点重新开始 */

        for (i = 0; i < LED_SHIFT_TIMES; i++)
        {
            LED_WriteAll(Pattern);
            Delay(LED_STEP_MS);
            Pattern = _crol_(Pattern, 1);    /* 两个低电平位一起向高位移动 */
        }
    }
}
