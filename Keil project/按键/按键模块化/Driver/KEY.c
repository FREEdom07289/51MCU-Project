/**
 * @file    KEY.c
 * @brief   独立按键驱动模块，提供带软件消抖的键值扫描
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-11
 * @note    硬件引脚（普中 A2 开发板）：
 *            K1 接 P3.1，按下为低电平
 *            K2 接 P3.0，按下为低电平
 *          依赖模块：Delay.c（提供毫秒延时）
 *          修改记录：
 *            V1.0 2026-11-11 从 05~08 四个单文件工程中抽取按键扫描逻辑
 */

#include <REGX52.H>
#include "KEY.h"
#include "Delay.h"

/* ==================== 私有宏与变量 ==================== */

/* 引脚定义放在 .c 内：sbit 写进头文件会被多个模块重复定义，链接报错 */
sbit KEY1 = P3^1;                   // K1
sbit KEY2 = P3^0;                   // K2

#define KEY_DEBOUNCE_MS 10          // 机械抖动约 5~10ms，取 10ms 消抖

/* ==================== 对外接口实现 ==================== */

/**
 * @brief  扫描独立按键，返回本次按下的键值
 * @param  None
 * @retval KEY_VALUE_NONE 无按键；KEY_VALUE_K1 / KEY_VALUE_K2 对应按键按下
 * @note   内部已做消抖与松手等待，一次按压只返回一次；
 *         函数会阻塞等待松手，不适合在中断中调用
 */
unsigned char KEY_Scan(void)
{
    if (KEY1 == 0)
    {
        Delay_ms(KEY_DEBOUNCE_MS);  // 首次读到低电平，先等抖动结束再确认
        if (KEY1 == 0)
        {
            while (KEY1 == 0)       // 等待松手，否则一次按压会被反复识别
            {
                ;
            }
            Delay_ms(KEY_DEBOUNCE_MS);  // 松手瞬间同样有抖动，再消抖一次
            return KEY_VALUE_K1;
        }
    }

    if (KEY2 == 0)
    {
        Delay_ms(KEY_DEBOUNCE_MS);
        if (KEY2 == 0)
        {
            while (KEY2 == 0)
            {
                ;
            }
            Delay_ms(KEY_DEBOUNCE_MS);
            return KEY_VALUE_K2;
        }
    }

    return KEY_VALUE_NONE;
}
