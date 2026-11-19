/**
 * @file    MatrixKey_Scan.c
 * @brief   4×4 矩阵键盘驱动模块（行列扫描），提供按键扫描接口
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    硬件引脚（普中 A2 开发板）：
 *            P1.7 ~ P1.4 接行线，P1.3 ~ P1.0 接列线，按下为低电平
 *          依赖模块：无
 *          修改记录：
 *            V1.0 2026-11-14 新建空白驱动，扫描逻辑待实现
 */
#include <REGX52.H>
#include "MatrixKey_Scan.h"

/* ==================== 对外接口实现 ==================== */
unsigned char MatrixKey_Scan(void)
{
    unsigned char key = 0 ;
    
    //扫描第一行，读取列
    P1 = 0x7F ;

    if((P1 & 0X0F != 0X0F))
    {
        Delay_ms(10) ; //消抖
        if((P1 & 0X0F) != 0X0F)
        {
            switch(P1 & 0X0F)
            {
                case 0x07: key =1; break;
                case 0x0B: key =2; break;
                case 0x0D: key =3; break;
                case 0x0E: key =4; break;
            }
            while((P1 & 0X0F) != 0X0F); //等待按键释放
            return key ;
        }
    }
    
    //扫描第二行，读取列
    P1 = 0xBF ;

    if((P1 & 0X0F != 0X0F))
    {
        Delay_ms(10) ; //消抖
        if((P1 & 0X0F) != 0X0F)
        {
            switch(P1 & 0X0F)
            {
                case 0x07: key =5; break;
                case 0x0B: key =6; break;
                case 0x0D: key =7; break;
                case 0x0E: key =8; break;
            }
            while((P1 & 0X0F) != 0X0F); //等待按键释放
            return key ;
        }
    }

    //扫描第三行，读取列
    P1 = 0xDF ;
    if((P1 & 0X0F != 0X0F))
    {
        Delay_ms(10) ; //消抖
        if((P1 & 0X0F) != 0X0F)
        {
            switch(P1 & 0X0F)
            {
                case 0x07: key =9; break;
                case 0x0B: key =10; break;
                case 0x0D: key =11; break;
                case 0x0E: key =12; break;
            }
            while((P1 & 0X0F) != 0X0F); //等待按键释放
            return key ;
        }
    }

    //扫描第四行,读取列
    P1 = 0xEF ;

    if((P1 & 0X0F != 0X0F))
    {
        Delay_ms(10) ; //消抖
        if((P1 & 0X0F) != 0X0F)
        {
            switch(P1 & 0X0F)
            {   
                case 0x07: key =13; break;
                case 0x0B: key =14; break;
                case 0x0D: key =15; break;
                case 0x0E: key =16; break;
            }
            while((P1 & 0X0F) != 0X0F); //等待按键释放
            return key ;
        }
    }

/* 扫描函数待实现 */
