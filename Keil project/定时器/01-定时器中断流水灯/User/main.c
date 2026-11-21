/**
 * @file    main.c
 * @brief   定时器中断实验：用 1ms 节拍实现 500ms 流水灯，全程不用 Delay
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-22
 * @note    硬件：STC89C52RC + 8 个 LED（P2.0~P2.7，低电平点亮）
 *          现象：D1 → D8 每 500ms 移动一位，循环流水；主循环里没有任何延时函数
 *          依赖模块：LED.c（点灯）、Timer0.c（1ms 节拍）
 *          修改记录：
 *            V1.0 2026-11-22 首版：定时器中断流水灯
 */
#include <REGX52.H>
#include <INTRINS.H>
#include "LED.h"
#include "Timer0.h"

/* ==================== 私有宏 ==================== */

#define STEP_MS     500     /* 流水灯每步停留时间，单位 ms */

/* ==================== 主函数 ==================== */

void main(void)
{
    unsigned char Pattern = 0xFE;           /* 0xFE：仅 D1 亮（P2.0 = 0） */
    unsigned int LastMs;

    LED_Init();
    LED_WriteAll(Pattern);

    Timer0_Init();                          /* 启动 1ms 节拍 */
    LastMs = Timer0_GetMs();

    while (1)
    {
        /* 非阻塞判断：走过 500ms 才动一步，其余时间主循环空闲 */
        if ((unsigned int)(Timer0_GetMs() - LastMs) >= STEP_MS)
        {
            LastMs += STEP_MS;              /* 固定节拍累加，避免每次误差累积 */

            Pattern = _crol_(Pattern, 1);   /* 循环左移：D1→D8 */
            LED_WriteAll(Pattern);
        }
    }
}