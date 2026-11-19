/**
 * @file    main.c
 * @brief   LED 点阵实验：显示心形图案
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    硬件：STC89C52RC + 8×8 LED 点阵 + 74HC595
 *          现象：点阵稳定显示一个心形图案
 *          修改记录：
 *            V1.0 2026-11-14 按模块化规范拆分 Driver/System/User，
 *                            74HC595 时序与列扫描移入 Driver/LEDDZ.c
 */
#include "LEDDZ.h"

/* ==================== 私有变量 ==================== */

/* 行数据：心形图案，1 表示该行点亮 */
static unsigned char code RowData[8] = {
    0x38, 0x7C, 0x7E, 0x3F, 0x3F, 0x7E, 0x7C, 0x38
};

/* 列数据：逐列输出低电平，依次选通第 1 ~ 8 列 */
static unsigned char code ColData[8] = {
    0x7F, 0xBF, 0xDF, 0xEF, 0xF7, 0xFB, 0xFD, 0xFE
};

/* ==================== 主函数 ==================== */

void main(void)
{
    while (1)
    {
        LEDDZ_DisplayFrame(RowData, ColData);   /* 扫描一轮，靠视觉暂留成图 */
    }
}
