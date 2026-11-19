/**
 * @file    main.c
 * @brief   数码管实验：动态扫描显示 0 ~ 7
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    硬件：STC89C52RC + 8 位共阴数码管（P0 段选，P2.2 ~ P2.4 接 74HC138 位选）
 *          现象：8 位数码管从左到右依次显示 0 ~ 7
 *          修改记录：
 *            V1.0 2026-11-14 按模块化规范拆分 Driver/System/User，
 *                            扫描改由 1ms 定时标志驱动，主循环负责刷新
 */
#include "SMG.h"
#include "Timer0.h"

/* ==================== 主函数 ==================== */

void main(void)
{
    unsigned char i;

    for (i = 0; i < SMG_NUM; i++)
    {
        SMG_Buf[i] = i;         /* 缓冲区内容即显示内容 */
    }

    Timer0_Init();              /* 中断每 1ms 置一次标志 */

    while (1)
    {
        if (Timer0_Tick)
        {
            Timer0_Tick = 0;    /* 先清标志，避免重复刷新 */
            SMG_Scan();         /* 每次切换一位，8ms 扫完一轮 */
        }
    }
}
