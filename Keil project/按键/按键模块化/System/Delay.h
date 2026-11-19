/**
 * @file    Delay.h
 * @brief   延时模块，提供毫秒级软件延时
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-11
 * @note    延时长度按 11.0592MHz 晶振标定，属于粗延时，
 *          只用于按键消抖、流水灯节奏等场合，不可用于精确计时
 *          修改记录：
 *            V1.0 2026-11-11 与 LCD1602_模块化 工程保持同一份实现
 */

#ifndef __DELAY_H
#define __DELAY_H

/* ==================== 对外接口声明 ==================== */

void Delay_ms(unsigned int Ms);

#endif
