/**
 * @file    BEEP.c
 * @brief   蜂鸣器驱动模块，按指定频率和时长输出方波
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    硬件引脚：P2.5 经 ULN2003D 驱动无源蜂鸣器
 *          依赖模块：Delay.c（提供 10us 级延时）
 *          修改记录：
 *            V1.0 2026-11-14 从蜂鸣器单文件代码中拆出方波播放功能
 */
#include <REGX52.H>
#include "BEEP.h"
#include "Delay.h"

/* ==================== 私有宏与变量 ==================== */

sbit BEEP_PIN = P2^5;       /* 蜂鸣器控制脚，方波翻转即发声 */

/* ==================== 对外接口实现 ==================== */

/**
 * @brief  以指定频率鸣叫指定时长
 * @param  Freq 发声频率，单位 Hz，取值 131 ~ 988；传 0 表示休止
 * @param  Ms   持续时长，单位毫秒，取值 1 ~ 65535
 * @retval None
 * @note   阻塞式方波输出，占用 CPU；半周期按 250000 / Freq 微秒计算，
 *         再折算成 10us 延时单位，换晶振后需重新标定
 */
void BEEP_PlayFreq(unsigned int Freq, unsigned int Ms)
{
    unsigned long CycleCnt;         /* 需要翻转的总次数，约等于 频率 × 时长 */
    unsigned int HalfPeriod;        /* 半周期的延时单位数，已折算成 10us 单位 */

    if (Freq == 0)
    {
        Delay_10us(500);            /* 休止：保持与原代码相同的短延时，节拍由拍数决定 */
        return;
    }

    CycleCnt = (unsigned long)Freq * Ms / 1000;
    HalfPeriod = 250000UL / Freq;   /* 半周期 = 500000 / Freq 微秒 */

    while (CycleCnt--)
    {
        BEEP_PIN = !BEEP_PIN;
        Delay_10us(HalfPeriod / 10);
    }
}
