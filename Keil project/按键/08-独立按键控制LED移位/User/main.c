/**
 * @file    main.c
 * @brief   独立按键控制 LED 移位主程序：K1 每按一次，点亮位置左移一位
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    硬件：STC89C52RC + 8 个 LED + 独立按键 K1
 *          引脚：LED 接 P2.0~P2.7（低电平点亮），K1 接 P3.1
 *          依赖模块：LED.c、KEY.c
 *          修改记录：
 *            V1.0 2026-11-14 按三层结构拆分为 Driver/System/User
 */

#include "LED.h"
#include "KEY.h"

/* ==================== 私有宏 ==================== */

#define LED_START_PATTERN  0xFE     /* 1111 1110，仅 D1 点亮 */

/* ==================== 主函数 ==================== */

void main(void)
{
    unsigned char LedPattern = LED_START_PATTERN;   /* 当前点亮图案 */

    LED_Init();
    LED_WriteAll(LedPattern);

    while (1)
    {
        if (KEY_Scan() == KEY_VALUE_K1)
        {
            LedPattern = (unsigned char)((LedPattern << 1) | 0x01);   /* 左移一位，最低位补 1 */

            if (LedPattern == 0xFF)     /* 8 个 LED 全灭说明已走完一轮，回到起点 */
            {
                LedPattern = LED_START_PATTERN;
            }

            LED_WriteAll(LedPattern);
        }
    }
}

/* ==================== 实验笔记 ==================== */

/*
注意事项：
1. 读取单个引脚标准写法是P3_1或sbit P3_1 = P3^1;，而不是P3^1.
2.机械按键在按下和释放的过程中会产生抖动现象，一般为5ms到10ms，可能会导致程序误判按键状态，因此需要进行消抖处理。
3.按下时和释放时都需要进行消抖处理，防止误判。
*/
