/**
 * @file    LCD1602.c
 * @brief   LCD1602 字符液晶驱动模块，提供初始化、光标定位与字符串显示
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-11
 * @note    硬件引脚（普中 A2 开发板）：
 *            DB0~DB7  接 P0.0~P0.7   8 位数据总线
 *            RS       接 P2.6         0=指令 1=显示数据
 *            RW       接 P2.5         0=写   1=读
 *            E        接 P2.7         高脉冲锁存，下降沿执行
 *          依赖模块：Delay.c（提供毫秒延时）
 *          修改记录：
 *            V1.0 2026-11-11 从原 LCD1602/main.c 拆分为独立驱动模块
 */

#include <REGX52.H>
#include <intrins.h>
#include "LCD1602.h"
#include "Delay.h"

/* ==================== 私有宏与变量 ==================== */

/* 引脚定义放在 .c 内：sbit 写进头文件会被多个模块重复定义，链接报错 */
sbit LCD1602_RS = P2^6;             // 指令/数据选择
sbit LCD1602_RW = P2^5;             // 读/写控制
sbit LCD1602_EN = P2^7;             // 使能信号

#define LCD1602_DATA        P0      // 8 位数据总线
#define LCD1602_CMD_FUNC8   0x38    // 8 位总线、双行显示、5×7 点阵
#define LCD1602_CMD_DISP_ON 0x0C    // 显示开、光标关、光标不闪烁
#define LCD1602_CMD_ENTRY   0x06    // 写入后光标右移、整屏不移动
#define LCD1602_CMD_CLEAR   0x01    // 清屏，光标回原点
#define LCD1602_LINE1_ADDR  0x80    // 第 1 行 DDRAM 首地址
#define LCD1602_LINE2_ADDR  0xC0    // 第 2 行 DDRAM 首地址

/* ==================== 私有函数声明 ==================== */

static void LCD1602_WriteCmd(unsigned char Cmd);
static void LCD1602_WriteData(unsigned char Dat);

/* ==================== 对外接口实现 ==================== */

/**
 * @brief  初始化 LCD1602
 * @param  None
 * @retval None
 * @note   上电后必须等内部复位完成再发指令，否则指令会被丢弃
 */
void LCD1602_Init(void)
{
    Delay_ms(20);                           // 上电复位需 > 15ms，留余量
    LCD1602_WriteCmd(LCD1602_CMD_FUNC8);
    Delay_ms(5);                            // 手册要求 > 4.1ms
    LCD1602_WriteCmd(LCD1602_CMD_FUNC8);    // 内部复位可能未完成，重复设置确保进入 8 位模式
    Delay_ms(1);                            // 手册要求 > 100us
    LCD1602_WriteCmd(LCD1602_CMD_FUNC8);

    LCD1602_WriteCmd(LCD1602_CMD_DISP_ON);
    LCD1602_WriteCmd(LCD1602_CMD_ENTRY);
    LCD1602_WriteCmd(LCD1602_CMD_CLEAR);

    Delay_ms(5);                            // 清屏执行时间较长，留足余量
}

/**
 * @brief  设置光标位置
 * @param  Line   行号，取值 1 或 2
 * @param  Column 列号，取值 1 ~ 16
 * @retval None
 * @note   行列从 1 开始计数，与屏幕观察习惯一致；本函数不校验越界值
 */
void LCD1602_SetCursor(unsigned char Line, unsigned char Column)
{
    if (Line == 1)
    {
        LCD1602_WriteCmd(LCD1602_LINE1_ADDR + Column - 1);   // 地址从 0 开始，故减 1
    }
    else if (Line == 2)
    {
        LCD1602_WriteCmd(LCD1602_LINE2_ADDR + Column - 1);
    }
}

/**
 * @brief  LCD1602 在指定行列显示字符串
 * @param  Line   显示行，取值 1 或 2
 * @param  Column 起始列，取值 1 ~ 16
 * @param  String 待显示字符串首地址，长度勿超过 (16 - Column + 1)
 * @retval None
 * @note   需先调用 LCD1602_Init()，否则显示乱码
 */
void LCD1602_ShowString(unsigned char Line, unsigned char Column, char *String)
{
    LCD1602_SetCursor(Line, Column);
    while (*String != '\0')                 // 逐字节写入，遇结束符停止
    {
        LCD1602_WriteData(*String);
        String++;
    }
}

/* ==================== 私有函数实现 ==================== */

/**
 * @brief  向 LCD1602 写入一条指令
 * @param  Cmd 指令字节，取值见本文件 LCD1602_CMD_xxx 宏
 * @retval None
 * @note   仅模块内部使用，函数内已包含指令执行所需的等待
 */
static void LCD1602_WriteCmd(unsigned char Cmd)
{
    LCD1602_RS = 0;                 // RS=0：本次传输的是指令
    LCD1602_RW = 0;                 // RW=0：MCU 写向 LCD
    LCD1602_EN = 0;                 // 先拉低，保证随后能产生完整高脉冲

    LCD1602_DATA = Cmd;

    LCD1602_EN = 1;                 // 高电平期间数据被送到总线
    _nop_();                        // 手册要求 E 高脉宽 > 450ns，两个空操作兜底
    _nop_();
    LCD1602_EN = 0;                 // 下降沿锁存并执行

    Delay_ms(2);                    // 普通指令执行 > 1.6ms，留余量
}

/**
 * @brief  向 LCD1602 写入一个显示数据
 * @param  Dat 待显示的字符 ASCII 码
 * @retval None
 * @note   仅模块内部使用，函数内已包含写入所需的等待
 */
static void LCD1602_WriteData(unsigned char Dat)
{
    LCD1602_RS = 1;                 // RS=1：本次传输的是显示数据
    LCD1602_RW = 0;
    LCD1602_EN = 0;

    LCD1602_DATA = Dat;

    LCD1602_EN = 1;
    _nop_();
    _nop_();
    LCD1602_EN = 0;

    Delay_ms(2);                    // 字符写入后同样需要等待内部处理
}
