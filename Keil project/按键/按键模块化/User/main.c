/**
 * @file    main.c
 * @brief   独立按键模块化工程主程序：K1 启停流水灯，K2 切换流水方向
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    硬件：STC89C52RC + 8 个 LED + 独立按键 K1/K2
 *          引脚：LED 接 P2.0~P2.7（低电平点亮），K1 接 P3.1，K2 接 P3.0
 *          依赖模块：LED.c、KEY.c、Delay.c
 *          修改记录：
 *            V1.0 2026-11-11 按模块化规范拆分 Driver/System/User，
 *                            以原 05 工程功能作为演示
 *            V1.0 2026-11-14 把 P2 口操作移入 LED 驱动，main 不再出现寄存器名
 */

#include <INTRINS.H>
#include "LED.h"
#include "KEY.h"
#include "Delay.h"

/* ==================== 私有宏与变量 ==================== */

#define LED_STEP_MS   200           /* 流水灯每步停留时间，单位 ms */

static unsigned char LedPattern = 0xFE;  /* 流水码值，0xFE 时仅 D1 亮 */
static unsigned char Direction  = 0;     /* 0=左移 D1→D8，1=右移 D8→D1 */
static unsigned char Run_Flag   = 1;     /* 1=运行，0=暂停 */

/* ==================== 主函数 ==================== */

void main(void)
{
    unsigned char Key;

    LED_Init();
    LED_WriteAll(LedPattern);           /* 上电先点亮 D1，避免全灭空档 */

    while (1)
    {
        Key = KEY_Scan();

        if (Key == KEY_VALUE_K1)
        {
            Run_Flag = !Run_Flag;       /* K1：运行与暂停之间切换 */
        }
        else if (Key == KEY_VALUE_K2)
        {
            Direction = !Direction;     /* K2：流水方向取反 */
        }

        if (Run_Flag)
        {
            LED_WriteAll(LedPattern);
            Delay_ms(LED_STEP_MS);      /* 阻塞期间不扫描按键，按键响应最慢约等于此值 */

            if (Direction == 0)
            {
                LedPattern = _crol_(LedPattern, 1);   /* 循环左移，D1→D8 */
            }
            else
            {
                LedPattern = _cror_(LedPattern, 1);   /* 循环右移，D8→D1 */
            }
        }
    }
}
