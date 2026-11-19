/**
 * @file    main.c
 * @brief   蜂鸣器实验：播放《稻香》间奏片段
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    硬件：STC89C52RC + 无源蜂鸣器（P2.5，经 ULN2003D 驱动）
 *          现象：循环播放《稻香》间奏旋律
 *          修改记录：
 *            V1.0 2026-11-14 按模块化规范拆分 Driver/System/User，
 *                            方波产生移入 Driver/BEEP.c，延时移入 System/Delay.c
 */
#include "BEEP.h"
#include "Delay.h"

/* ==================== 私有宏与变量 ==================== */

#define NOTE_UNIT_MS    180     /* 一拍时长，单位 ms，按原代码 180ms/拍 */

/* 音名频率表：0 为休止，1~7 中音，8~14 高音，15~21 低音 */
static unsigned int code FreqTable[22] = {
    0,
    262, 294, 330, 349, 392, 440, 494,     /* 中音 1 ~ 7 */
    523, 587, 659, 698, 784, 880, 988,     /* 高音 1 ~ 7 */
    131, 147, 165, 175, 196, 220, 247      /* 低音 1 ~ 7 */
};

/* 乐谱：每行 {音名, 拍数}，{0, 0} 为结束标记 */
static unsigned char code Melody[][2] = {
    {8, 2}, {10, 2}, {12, 2}, {0, 2}, {16, 2}, {21, 2}, {19, 3},
    {8, 2}, {10, 2}, {12, 2}, {0, 2}, {16, 2}, {21, 2}, {19, 3},
    {8, 2}, {19, 2}, {8, 2}, {19, 2},
    {8, 6},
    {0, 0}
};

/* ==================== 私有函数声明 ==================== */

static void PlayNote(unsigned char Note, unsigned char Beats);

/* ==================== 主函数 ==================== */

void main(void)
{
    unsigned char i;

    while (1)
    {
        for (i = 0; Melody[i][0] != 0 || Melody[i][1] != 0; i++)
        {
            PlayNote(Melody[i][0], Melody[i][1]);
        }

        Delay_10us(30000);      /* 一遍播完停顿约 300ms 再循环 */
    }
}

/* ==================== 私有函数实现 ==================== */

/**
 * @brief  按音名和拍数播放一个音符
 * @param  Note  音名下标，取值 0 ~ 21，对应 FreqTable 的下标
 * @param  Beats 持续拍数，取值 1 ~ 6
 * @retval None
 * @note   拍数换算成毫秒后再交给驱动播放，音名 0 表示休止
 */
static void PlayNote(unsigned char Note, unsigned char Beats)
{
    BEEP_PlayFreq(FreqTable[Note], (unsigned int)Beats * NOTE_UNIT_MS);
}
