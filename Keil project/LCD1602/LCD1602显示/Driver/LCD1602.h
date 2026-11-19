/**
 * @file    LCD1602.h
 * @brief   LCD1602 字符液晶驱动模块对外接口
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    硬件引脚（普中 A2 开发板）：
 *            DB0 ~ DB7 接 P0.0 ~ P0.7，RS 接 P2.6，RW 接 P2.5，E 接 P2.7
 *          修改记录：
 *            V1.0 2026-11-14 从 LCD1602 单文件代码中拆出独立驱动模块
 */

#ifndef __LCD1602_H
#define __LCD1602_H

/* ==================== 对外接口声明 ==================== */

void LCD1602_Init(void);
void LCD1602_SetCursor(unsigned char Line, unsigned char Column);
void LCD1602_ShowString(unsigned char Line, unsigned char Column, char *String);
void LCD1602_ShowNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length);

#endif
