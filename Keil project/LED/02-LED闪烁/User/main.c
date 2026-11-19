/**
 * @file    main.c
 * @brief   LED 实验 02：8 个 LED 同步闪烁
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    硬件：STC89C52 + 8 位 LED（P2.0 ~ P2.7，低电平点亮）
 *          现象：全部 LED 亮 500ms、灭 500ms，循环往复
 *          修改记录：
 *            V1.0 2026-11-14 按模块化规范重组，P2 口操作移入 Driver/LED.c
 */
#include <REGX52.H>
#include "LED.h"
#include "Delay.h"

/* ==================== 宏定义 ==================== */

#define LED_BLINK_MS    500     /* 单次亮或灭的持续时间，单位毫秒 */

/* ==================== 主函数 ==================== */

void main(void)
{
    LED_Init();

    while (1)
    {
        LED_AllOn();
        Delay(LED_BLINK_MS);
        LED_AllOff();
        Delay(LED_BLINK_MS);
    }
}

