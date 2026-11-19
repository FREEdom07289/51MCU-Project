/**
 * @file    LEDDZ.h
 * @brief   LED 点阵驱动模块对外接口
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    硬件引脚：P0 列选，P3.4 SER、P3.5 RCLK、P3.6 SRCLK 接 74HC595
 *          修改记录：
 *            V1.0 2026-11-14 从点阵单文件代码中拆出 74HC595 时序与扫描
 */

#ifndef __LEDDZ_H
#define __LEDDZ_H

/* ==================== 对外接口声明 ==================== */

void LEDDZ_DisplayFrame(unsigned char code *RowData, unsigned char code *ColData);

#endif
