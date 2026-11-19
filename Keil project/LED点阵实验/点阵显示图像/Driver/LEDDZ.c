/**
 * @file    LEDDZ.c
 * @brief   LED 点阵驱动模块，提供 74HC595 串行写入与整帧扫描
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    硬件引脚：P0 列选，P3.4 SER、P3.5 RCLK、P3.6 SRCLK 接 74HC595
 *          依赖模块：Delay.c（提供 10us 级延时，满足 595 时序）
 *          修改记录：
 *            V1.0 2026-11-14 从点阵单文件代码中拆出 74HC595 时序与扫描
 */
#include <REGX52.H>
#include "LEDDZ.h"
#include "Delay.h"

/* ==================== 私有宏与引脚 ==================== */

sbit HC595_SER  = P3^4;     /* 串行数据输入 */
sbit HC595_RCLK = P3^5;     /* 存储寄存器时钟，上升沿输出到并行口 */
sbit HC595_SRCLK = P3^6;    /* 移位寄存器时钟，上升沿移入一位 */

#define LEDDZ_COL_PORT  P0  /* 列选端口，低电平选通对应列 */
#define LEDDZ_COLS      8   /* 点阵列数 */

/* ==================== 私有函数声明 ==================== */

static void HC595_WriteByte(unsigned char Dat);

/* ==================== 对外接口实现 ==================== */

/**
 * @brief  扫描显示一帧点阵图像
 * @param  RowData 行数据首地址，长度固定 8 字节，1 表示点亮
 * @param  ColData 列选数据首地址，长度固定 8 字节，0 表示该列选通
 * @retval None
 * @note   逐列扫描，每列保持约 1ms；靠视觉暂留形成完整图像
 */
void LEDDZ_DisplayFrame(unsigned char code *RowData, unsigned char code *ColData)
{
    unsigned char i;

    for (i = 0; i < LEDDZ_COLS; i++)
    {
        LEDDZ_COL_PORT = ColData[i];        /* 先选列，避免换列瞬间串影 */
        HC595_WriteByte(RowData[i]);        /* 再送该列的行数据 */
        Delay_10us(100);                    /* 保持约 1ms，保证亮度 */
        HC595_WriteByte(0x00);              /* 消影，防止下一列带残影 */
    }
}

/* ==================== 私有函数实现 ==================== */

/**
 * @brief  向 74HC595 写入一个字节
 * @param  Dat 待写入数据，高位先出
 * @retval None
 * @note   先移入 8 位，再由 RCLK 上升沿一次性锁存到并行输出
 */
static void HC595_WriteByte(unsigned char Dat)
{
    unsigned char i;

    for (i = 0; i < 8; i++)
    {
        HC595_SER = (Dat & 0x80) ? 1 : 0;   /* 取最高位送入串行口 */
        Dat <<= 1;
        HC595_SRCLK = 0;
        Delay_10us(1);
        HC595_SRCLK = 1;                    /* 上升沿移入一位 */
        Delay_10us(1);
    }

    HC595_RCLK = 1;
    Delay_10us(1);
    HC595_RCLK = 0;                         /* 上升沿后锁存，数据出现在并行口 */
}
