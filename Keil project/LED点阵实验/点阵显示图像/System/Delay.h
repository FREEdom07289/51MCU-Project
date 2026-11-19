/**
 * @file    Delay.h
 * @brief   延时模块对外接口
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    延时长度按 11.0592MHz 晶振标定，属于粗延时
 *          修改记录：
 *            V1.0 2026-11-14 从点阵单文件代码中拆出延时函数
 */

#ifndef __DELAY_H
#define __DELAY_H

/* ==================== 对外接口声明 ==================== */

void Delay_10us(unsigned int TenUs);

#endif
