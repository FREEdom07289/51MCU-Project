/**
 * @file    SMG.h
 * @brief   数码管驱动模块对外接口
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    硬件引脚：P0 段选（a ~ dp），P2.2 ~ P2.4 接 74HC138 位选
 *          修改记录：
 *            V1.0 2026-11-14 从动态数码管单文件代码中拆出扫描驱动
 */

#ifndef __SMG_H
#define __SMG_H

#include <REGX52.H>

/* ==================== 位数与接口定义 ==================== */

#define SMG_NUM     8       /* 数码管位数，即位选路数 */

/* 显示缓冲区：主循环写、中断以外的扫描函数读，volatile 防止读取被优化 */
extern volatile unsigned char SMG_Buf[SMG_NUM];

/* ==================== 对外接口声明 ==================== */

void SMG_Scan(void);

#endif
