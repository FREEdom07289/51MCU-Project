/**
 * @file    MatrixKey_Scan.h
 * @brief   4×4 矩阵键盘驱动模块对外接口
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    硬件引脚（普中 A2 开发板）：
 *            P1.7 ~ P1.4 接行线，P1.3 ~ P1.0 接列线，按下为低电平
 *          修改记录：
 *            V1.0 2026-11-14 新建空白驱动，扫描接口待实现
 */

#ifndef __MATRIXKEY_SCAN_H
#define __MATRIXKEY_SCAN_H

#include <REGX52.H>

/* ==================== 引脚定义 ==================== */

#define KEYPAD_PORT     P1      /* 矩阵键盘接 P1 口 */
#define KEYPAD_ROW_MASK 0x0F    /* P1.7 ~ P1.4 行线，扫描时逐行输出低电平 */
#define KEYPAD_COL_MASK 0xF0    /* P1.3 ~ P1.0 列线，读回列状态 */

/* ==================== 对外接口声明 ==================== */

/* 扫描接口待实现，暂不声明，避免骨架阶段产生未调用告警 */

#endif
