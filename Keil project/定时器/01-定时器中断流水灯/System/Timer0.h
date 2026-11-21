/**
 * @file    Timer0.h
 * @brief   定时器 0 系统模块：1ms 中断节拍 + 毫秒计数
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-22
 * @note    晶振 11.0592MHz，T0 方式 1（16 位定时），每 1ms 溢出一次；
 *          中断里只重装初值、累加毫秒，不做任何耗时操作
 *          修改记录：
 *            V1.0 2026-11-22 初版：1ms 节拍 + Timer0_GetMs 毫秒计数
 */

#ifndef __TIMER0_H
#define __TIMER0_H

/* ==================== 对外接口声明 ==================== */

void Timer0_Init(void);
unsigned int Timer0_GetMs(void);

#endif