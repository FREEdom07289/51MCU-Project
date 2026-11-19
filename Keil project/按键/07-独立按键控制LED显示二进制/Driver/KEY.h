/**
 * @file    KEY.h
 * @brief   独立按键驱动模块对外接口
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    硬件引脚：K1 -> P3.1，按下为低电平
 *          修改记录：
 *            V1.0 2026-11-14 初版，从 07 工程单文件代码中抽取按键扫描逻辑
 */

#ifndef __KEY_H
#define __KEY_H

/* ==================== 键值定义 ==================== */

#define KEY_VALUE_NONE  0   /* 无按键按下 */
#define KEY_VALUE_K1    1   /* K1 按下，对应 P3.1 */

/* ==================== 对外接口声明 ==================== */

unsigned char KEY_Scan(void);

#endif
