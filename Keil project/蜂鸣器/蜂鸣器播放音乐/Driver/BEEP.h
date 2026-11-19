/**
 * @file    BEEP.h
 * @brief   蜂鸣器驱动模块对外接口
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    硬件引脚：P2.5 经 ULN2003D 驱动无源蜂鸣器，需方波才能发声
 *          修改记录：
 *            V1.0 2026-11-14 从蜂鸣器单文件代码中拆出方波播放功能
 */

#ifndef __BEEP_H
#define __BEEP_H

/* ==================== 对外接口声明 ==================== */

void BEEP_PlayFreq(unsigned int Freq, unsigned int Ms);

#endif
