/**
 * @file    main.c
 * @brief   LED 实验 03（方案 B）：使用 _crol_ / _cror_ 库函数实现双向流水灯
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
#define LED_STEP_MS         500     /* 每步停留时间，单位毫秒 */

/* ==================== 主函数 ==================== */

void main(void)
{
    unsigned char Pattern = LED_START_PATTERN;   /* 当前输出图案 */
    unsigned char i;                             /* 移位步数计数器 */

    LED_Init();

    while (1)
    {
        /* 正向：D1 → D8 */
        for (i = 0; i < LED_SHIFT_TIMES; i++)
        {
            LED_WriteAll(Pattern);
            Delay(LED_STEP_MS);
            Pattern = _crol_(Pattern, 1);   /* 循环左移 1 位，最高位补到最低位 */
        }

        /* 反向：D8 → D1 */
        for (i = 0; i < LED_SHIFT_TIMES; i++)
        {
            LED_WriteAll(Pattern);
            Delay(LED_STEP_MS);
            Pattern = _cror_(Pattern, 1);   /* 循环右移 1 位，最低位补到最高位 */
        }
    }
}

