/**
 * @file    main.c
 * @brief   LCD1602 模块化工程主程序：两行静态字符显示
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-11
 * @note    硬件：STC89C52RC + LCD1602
 *          引脚：P0 数据总线，P2.6 RS，P2.5 RW，P2.7 E
 *          依赖模块：Driver/LCD1602.c
 *          修改记录：
 *            V1.0 2026-11-11 按模块化规范拆分 Driver/System/User
 */

#include "LCD1602.h"

/* ==================== 主函数 ==================== */

void main(void)
{
    LCD1602_Init();                                 // 初始化必须在任何显示操作之前
    LCD1602_ShowString(1, 1, "Hello, World!");      // 第 1 行第 1 列
    LCD1602_ShowString(2, 1, "51 MCU Study");       // 第 2 行第 1 列

    while (1)
    {
        /* 显示内容为静态，主循环空闲，后续功能在此扩展 */
    }
}
