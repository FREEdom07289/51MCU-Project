/**
 * @file    LED.c
 * @brief   LED 驱动模块，提供端口初始化与单灯点亮
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
 * @brief  只点亮指定编号的一路 LED，其余熄灭
 * @param  Index LED 编号，取值 0 ~ 7，依次对应 D1 ~ D8
 * @retval None
 * @note   Index 超出 0 ~ 7 时结果无意义，调用者需自行保证范围
 */
void LED_OnOne(unsigned char Index)
{
    LED_PORT = ~(0x01 << Index);
}
