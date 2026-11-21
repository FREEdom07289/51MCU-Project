/**
 * @file    LCD1602.h
 * @brief   LCD1602 字符液晶驱动模块接口声明
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-11
 * @note    硬件引脚：DB0~DB7 -> P0，RS -> P2.6，RW -> P2.5，E -> P2.7
 *          依赖模块：Delay.c（提供毫秒延时）
 *          修改记录：
 *            V1.0 2026-11-11 从原 LCD1602/main.c 拆分为独立驱动模块
 */

#ifndef __LCD1602_H
#define __LCD1602_H

/* ==================== 对外接口声明 ==================== */

void LCD1602_Init(void);
void LCD1602_SetCursor(unsigned char Line, unsigned char Column);
void LCD1602_ShowString(unsigned char Line, unsigned char Column, char *String);

#endif
