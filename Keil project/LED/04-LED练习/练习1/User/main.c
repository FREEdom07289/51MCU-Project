/**
 * @file    main.c
 * @brief   LED 练习 01：8 个 LED 全亮 1s、全灭 0.5s 循环
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    硬件：STC89C52 + 8 位 LED（P2.0 ~ P2.7，低电平点亮）
 *          现象：全部 LED 亮 1s、灭 0.5s，循环往复
 *          修改记录：
 *            V1.0 2026-11-14 按模块化规范重组，P2 口操作移入 Driver/LED.c
 */
#include <REGX52.H>
#include "LED.h"
#include "Delay.h"

/* ==================== 宏定义 ==================== */

#define LED_ON_MS   1000    /* 全亮持续时间，单位毫秒 */
#define LED_OFF_MS  500     /* 全灭持续时间，单位毫秒 */

/* ==================== 主函数 ==================== */

void main(void)
{
    LED_Init();

    while (1)
    {
        LED_AllOn();
        Delay(LED_ON_MS);
        LED_AllOff();
        Delay(LED_OFF_MS);
    }
}
