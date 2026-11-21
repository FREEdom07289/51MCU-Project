/**
 * @file    Delay.h
 * @brief   延时模块，提供毫秒级软件延时
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-11
 * @note    延时长度按 11.0592MHz 晶振标定，属于粗延时，
 *          只用于 LCD 等低速外设的时序等待，不可用于精确计时
 *          修改记录：
 *            V1.0 2026-11-11 从原 LCD1602/main.c 拆分为独立模块
 */

#ifndef __DELAY_H
#define __DELAY_H

/* ==================== 对外接口声明 ==================== */

void Delay_ms(unsigned int ms);

#endif
