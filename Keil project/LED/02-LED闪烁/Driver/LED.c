/**
 * @file    LED.c
 * @brief   LED 驱动模块，提供端口初始化与全亮全灭
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    硬件引脚：P2.0 ~ P2.7 接 8 个 LED，低电平点亮
 *          依赖模块：无
 *          修改记录：
 *            V1.0 2026-11-14 初版，从各 LED 实验的 main.c 中抽取 P2 口操作
 */
#include "LED.h"

/* ==================== 对外接口实现 ==================== */

/**
 * @brief  初始化 LED 端口，全部熄灭
 * @retval None
 * @note   上电复位后 P2 默认即为高电平，这里显式写出，避免依赖复位默认值
 */
void LED_Init(void)
{
    LED_PORT = LED_ALL_OFF;
}

/**
 * @brief  点亮全部 LED
 * @retval None
 */
void LED_AllOn(void)
{
    LED_PORT = LED_ALL_ON;
}

/**
 * @brief  熄灭全部 LED
 * @retval None
 */
void LED_AllOff(void)
{
    LED_PORT = LED_ALL_OFF;
}
