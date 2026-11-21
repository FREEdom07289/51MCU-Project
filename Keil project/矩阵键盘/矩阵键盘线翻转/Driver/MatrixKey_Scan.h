/**
 * @file    MatrixKey_Scan.h
 * @brief   4×4 矩阵键盘驱动对外接口（线翻转法实现）
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-22
 * @note    硬件引脚（普中 A2 开发板）：
 *            P1.7 ~ P1.4 为行线，P1.3 ~ P1.0 为列线；
 *            线翻转法两次扫描时，行线和列线会互换“输出/输入”角色
 *          键号规则：第 1 行 S1~S4，第 2 行 S5~S8，第 3 行 S9~S12，第 4 行 S13~S16
 *          修改记录：
 *            V1.0 2026-11-22 新建，用“行低读列 + 列低读行”两次翻转替代逐列扫描
 */

#ifndef __MATRIX_KEY_SCAN_H
#define __MATRIX_KEY_SCAN_H

#include <REGX52.H>

/* ==================== 对外宏 ==================== */

#define KEYPAD_PORT         P1      /* 矩阵键盘接 P1 口 */
#define KEYPAD_COL_MASK     0x0F    /* P1.3 ~ P1.0：列线 */
#define KEYPAD_ROW_MASK     0xF0    /* P1.7 ~ P1.4：行线 */
#define KEYPAD_NO_KEY       0       /* 无键按下时的返回值 */

/* ==================== 对外接口声明 ==================== */

unsigned char MatrixKey_Scan(void);

#endif