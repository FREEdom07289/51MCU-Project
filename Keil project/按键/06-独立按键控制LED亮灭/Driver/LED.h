/**
 * @file    LED.h
 * @brief   LED 驱动模块对外接口
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    硬件引脚：D1 接 P2.0，低电平点亮
 *          修改记录：
 *            V1.0 2026-11-14 初版，从 06 工程单文件代码中抽取 P2.0 操作
 */

#ifndef __LED_H
#define __LED_H

#include <REGX52.H>

/* ==================== 引脚与图案定义 ==================== */

#define LED_PORT        P2          /* LED 所在端口 */
#define LED_ALL_OFF     0xFF        /* 全灭图案，8 位全为高电平 */

/* ==================== 对外接口声明 ==================== */

void LED_Init(void);
void LED_Toggle(void);

#endif
