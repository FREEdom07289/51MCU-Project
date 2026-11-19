/**
 * @file    SMG.h
 * @brief   数码管驱动模块对外接口
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    硬件引脚：P0.0 ~ P0.7 经 74HC245 接数码管 a ~ dp，共阴数码管高电平点亮
 *          修改记录：
 *            V1.0 2026-11-14 从静态数码管单文件代码中拆出段码表与段选输出
 */

#ifndef __SMG_H
#define __SMG_H

#include <REGX52.H>

/* ==================== 引脚与字符定义 ==================== */

#define SMG_SEG_PORT    P0      /* 段选端口，bit0 ~ bit7 依次对应 a ~ dp */
#define SMG_CHAR_A      10      /* 段码表下标，对应字符 A */

/* ==================== 对外接口声明 ==================== */

void SMG_ShowChar(unsigned char Index);

#endif
