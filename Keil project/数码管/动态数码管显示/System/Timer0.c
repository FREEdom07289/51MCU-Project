/**
 * @file    Timer0.c
 * @brief   定时器0模块，提供 1ms 周期中断
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    硬件资源：片内定时器0，工作方式1；按 12MHz 晶振计算，1ms 需 1000 个机器周期
 *          依赖模块：无
 *          修改记录：
 *            V1.0 2026-11-14 从动态数码管单文件代码中拆出定时器模块
 */
#include <REGX52.H>
#include "Timer0.h"

/* ==================== 私有宏与变量 ==================== */

#define T0_RELOAD   (65536 - TIMER0_TICK_MS * 1000)     /* 计数初值，12MHz 下溢出周期 1ms */

volatile bit Timer0_Tick = 0;

/* ==================== 对外接口实现 ==================== */

/**
 * @brief  初始化定时器0为 1ms 定时中断
 * @retval None
 * @note   只改 TMOD 低 4 位，不影响定时器1；同时打开总中断
 */
void Timer0_Init(void)
{
    TMOD = (TMOD & 0xF0) | 0x01;    /* 定时器0 方式1：16 位定时 */
    TH0 = T0_RELOAD / 256;
    TL0 = T0_RELOAD % 256;
    ET0 = 1;                        /* 允许定时器0 中断 */
    EA  = 1;                        /* 打开总中断 */
    TR0 = 1;                        /* 启动定时器0 */
}

/* ==================== 中断服务函数 ==================== */

/**
 * @brief  定时器0中断服务函数，每 1ms 触发一次
 * @note   中断号 1；只重装初值并置标志，刷新动作交由主循环完成
 */
void Timer0_ISR(void) interrupt 1
{
    TH0 = T0_RELOAD / 256;
    TL0 = T0_RELOAD % 256;
    Timer0_Tick = 1;
}
