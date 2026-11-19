/**
 * @file    main.c
 * @brief   独立按键控制流水灯主程序：K1 启停流水，K2 切换方向
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    硬件：STC89C52RC + 8 个 LED + 独立按键 K1/K2
 *          引脚：LED 接 P2.0~P2.7（低电平点亮），K1 接 P3.1，K2 接 P3.0
 *          依赖模块：LED.c、KEY.c、Delay.c
 *          修改记录：
 *            V1.0 2026-11-14 按三层结构拆分为 Driver/System/User
 */

#include <INTRINS.H>
#include "LED.h"
#include "KEY.h"
#include "Delay.h"

/* ==================== 私有宏 ==================== */

#define LED_STEP_MS  200    /* 流水灯每步停留时间，单位 ms */

/* ==================== 主函数 ==================== */

void main(void)
{
    unsigned char LedPattern = 0xFE;    /* 流水图案，0xFE 时只有 D1 点亮 */
    unsigned char Direction  = 0;       /* 0=左移 D1→D8，1=右移 D8→D1 */
    unsigned char Run_Flag   = 1;       /* 1=流水运行，0=暂停 */

    LED_Init();
    LED_WriteAll(LedPattern);           /* 上电先点亮 D1，避免全灭空档 */

    while (1)
    {
        switch (KEY_Scan())
        {
            case KEY_VALUE_K1:          /* K1：运行与暂停之间切换 */
                Run_Flag = !Run_Flag;
                break;

            case KEY_VALUE_K2:          /* K2：流水方向取反 */
                Direction = !Direction;
                break;

            default:
                break;
        }

        if (Run_Flag)
        {
            LED_WriteAll(LedPattern);
            Delay_ms(LED_STEP_MS);      /* 阻塞期间不扫描按键，按键响应最慢约 200ms */

            if (Direction == 0)
            {
                LedPattern = _crol_(LedPattern, 1);     /* 循环左移，D1→D8 */
            }
            else
            {
                LedPattern = _cror_(LedPattern, 1);     /* 循环右移，D8→D1 */
            }
        }
    }
}
