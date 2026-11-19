/**
 * @file    LED.c
 * @brief   LED 驱动模块，提供端口初始化与单灯翻转
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    硬件引脚：D1 接 P2.0，低电平点亮
 *          依赖模块：无
 *          修改记录：
 *            V1.0 2026-11-14 初版，从 06 工程单文件代码中抽取 P2.0 操作
 */
#include "LED.h"

/* ==================== 私有引脚 ==================== */

sbit LED_D1 = P2^0;     /* D1：低电平点亮 */

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
 * @brief  翻转 D1 的亮灭状态
 * @retval None
 * @note   只改 P2.0 一位，其余 LED 状态保持不变
 */
void LED_Toggle(void)
{
    LED_D1 = !LED_D1;
}
