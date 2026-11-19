/**
 * @file    MatrixKey_Scan.h
 * @brief   4×4 矩阵键盘驱动对外接口
 * @author  FREEDOM
 * @version V1.1
 * @date    2026-11-20
 * @note    硬件引脚（普中 A2 开发板）：
 *            P1.3 ~ P1.0 为列线（扫描时逐列输出低电平），
 *            P1.7 ~ P1.4 为行线（读回，按下时对应行为低电平）
 *          键号规则：第 1 行 S1~S4，第 2 行 S5~S8，第 3 行 S9~S12，第 4 行 S13~S16
 *          修改记录：
 *            V1.0 2026-11-14 新建空白驱动，列/行掩码写反
 *            V1.1 2026-11-20 补全扫描接口声明，修正掩码并写清键号规则
 */

#ifndef __MATRIX_KEY_SCAN_H
#define __MATRIX_KEY_SCAN_H

#include <REGX52.H>

/* ==================== 对外宏 ==================== */

#define KEYPAD_PORT         P1      /* 矩阵键盘接 P1 口 */
#define KEYPAD_COL_MASK     0x0F    /* P1.3 ~ P1.0：列线，低 4 位 */
#define KEYPAD_ROW_MASK     0xF0    /* P1.7 ~ P1.4：行线，高 4 位 */
#define KEYPAD_NO_KEY       0       /* 无键按下时的返回值 */

/* ==================== 对外接口声明 ==================== */

unsigned char MatrixKey_Scan(void);

#endif