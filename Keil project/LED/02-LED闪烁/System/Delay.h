/**
 * @file    Delay.h
 * @brief   软件延时模块对外接口
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    依赖模块：无（纯空循环，不占用定时器资源）
 *          修改记录：
 *            V1.0 2026-11-14 初版，统一各 LED 实验里各自的延时写法
 */
#ifndef __DELAY_H
#define __DELAY_H

/* ==================== 对外接口声明 ==================== */

void Delay(unsigned int Ms);

#endif
