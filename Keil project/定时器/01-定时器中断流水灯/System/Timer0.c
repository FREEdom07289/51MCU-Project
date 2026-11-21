/**
 * @file    Timer0.c
 * @brief   定时器 0 系统模块：1ms 中断节拍 + 毫秒计数
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-22
 * @note    定时器初值按 11.0592MHz 晶振计算：
 *            机器周期 = 12 / 11.0592MHz ≈ 1.085us
 *            1ms 需要 1000 / 1.085 ≈ 922 个机器周期
 *            65536 - 922 = 64614 = 0xFC66
 *          依赖：无
 *          修改记录：
 *            V1.0 2026-11-22 初版：T0 方式 1、1ms 中断、毫秒计数
 */

#include <REGX52.H>
#include "Timer0.h"

/* ==================== 私有宏与变量 ==================== */

#define TIMER0_1MS_H    0xFC        /* 1ms 初值高 8 位 */
#define TIMER0_1MS_L    0x66        /* 1ms 初值低 8 位 */

/* volatile：中断里修改、主循环里读取，必须告诉编译器“会随时变”，不能优化进寄存器 */
static volatile unsigned int Timer0_Ms = 0;

/* ==================== 对外接口实现 ==================== */

/**
 * @brief  初始化定时器 0：方式 1，1ms 中断
 * @retval None
 * @note   TMOD 不可位寻址，只能整字节改：先清 T0 的 4 位，再写入方式 1
 */
void Timer0_Init(void)
{
    TMOD &= 0xF0;                   /* 保留 T1 的设置，清掉 T0 的低 4 位 */
    TMOD |= 0x01;                   /* T0 方式 1：16 位定时器 */

    TH0 = TIMER0_1MS_H;             /* 先装初值，再启动，避免第一次溢出过快 */
    TL0 = TIMER0_1MS_L;

    ET0 = 1;                        /* 允许 T0 中断 */
    EA  = 1;                        /* 打开总中断 */
    TR0 = 1;                        /* 启动 T0 */
}

/**
 * @brief  读取上电以来累计的毫秒数
 * @retval 0 ~ 65535 毫秒（约 65.5 秒后回绕）
 * @note   读 16 位变量时先关 ET0：51 是 8 位机，读高低字节之间若被中断打断，
 *          可能读到“半新半旧”的值；关中断保证这次读取是原子的
 */
unsigned int Timer0_GetMs(void)
{
    unsigned int Value;

    ET0 = 0;
    Value = Timer0_Ms;
    ET0 = 1;

    return Value;
}

/* ==================== 中断服务函数 ==================== */

/**
 * @brief  定时器 0 中断：每 1ms 进入一次
 * @note   中断号 1 对应 T0；必须手动重装初值（方式 1 不会自动重装）
 *         中断里只做“重装 + 计数”，绝不调用延时、显示等耗时函数
 */
void Timer0_ISR(void) interrupt 1
{
    TH0 = TIMER0_1MS_H;
    TL0 = TIMER0_1MS_L;
    Timer0_Ms++;
}