/**
 * @file    Timer0.h
 * @brief   定时器0模块对外接口
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    硬件资源：片内定时器0，工作方式1（16 位定时）
 *          修改记录：
 *            V1.0 2026-11-14 从动态数码管单文件代码中拆出定时器模块
 */

#ifndef __TIMER0_H
#define __TIMER0_H

/* ==================== 周期与标志定义 ==================== */

#define TIMER0_TICK_MS  1       /* 中断周期，单位 ms */

extern volatile bit Timer0_Tick;    /* 溢出标志，中断置 1、主循环清 0 */

/* ==================== 对外接口声明 ==================== */

void Timer0_Init(void);

#endif
