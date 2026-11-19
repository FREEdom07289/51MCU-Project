/**
 * @file    LED.h
 * @brief   LED 驱动模块对外接口
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    硬件引脚：P2.0 ~ P2.7 接 8 个 LED，低电平点亮
 *          修改记录：
 *            V1.0 2026-11-14 初版，从各 LED 实验的 main.c 中抽取 P2 口操作
 *            V1.0 2026-11-14 补充 LED_AllOff，供扫描到无效按键时整组熄灭
 */
#ifndef __LED_H
#define __LED_H

#include <REGX52.H>

/* ==================== 对外宏 ==================== */

#define LED_PORT        P2          /* LED 连接端口，D1 ~ D8 对应 P2.0 ~ P2.7 */
#define LED_ALL_ON      0x00        /* 全亮图案，8 位全为低电平 */
#define LED_ALL_OFF     0xFF        /* 全灭图案，8 位全为高电平 */

/* ==================== 对外接口声明 ==================== */

void LED_Init(void);
void LED_AllOff(void);
void LED_OnOne(unsigned char Index);

#endif
