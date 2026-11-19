/**
 * @file    Delay.h
 * @brief   延时模块对外接口
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    延时长度按 11.0592MHz 晶振标定，属粗延时，
 *          只用于按键消抖、流水灯节奏等场合，不可用于精确计时
 *          修改记录：
 *            V1.0 2026-11-14 初版，从按键实验的 main.c 中抽取延时函数
 */

#ifndef __DELAY_H
#define __DELAY_H

/* ==================== 对外接口声明 ==================== */

void Delay_ms(unsigned int Ms);

#endif
