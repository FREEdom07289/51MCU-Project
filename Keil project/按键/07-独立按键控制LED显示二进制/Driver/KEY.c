/**
 * @file    KEY.c
 * @brief   独立按键驱动模块，提供带软件消抖的键值扫描
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    硬件引脚（普中 A2 开发板）：K1 接 P3.1，按下为低电平
 *          依赖模块：Delay.c（提供毫秒延时）
 *          修改记录：
 *            V1.0 2026-11-14 初版，从 07 工程单文件代码中抽取按键扫描逻辑
 */
#include <REGX52.H>
#include "KEY.h"
#include "Delay.h"

/* ==================== 私有宏与引脚 ==================== */

#define KEY_DEBOUNCE_MS  20     /* 机械抖动约 5~10ms，取 20ms 留足裕量 */

/* 引脚定义放在 .c 内：sbit 写进头文件会被多个模块重复定义，链接报错 */
sbit KEY_1 = P3^1;              /* K1 */

/* ==================== 对外接口实现 ==================== */

/**
 * @brief  扫描独立按键，返回本次按下的键值
 * @retval KEY_VALUE_NONE 无按键；KEY_VALUE_K1 表示 K1 按下
 * @note   内部已做消抖与松手等待，一次按压只返回一次；
 *         函数阻塞等待松手，不适合在中断中调用
 */
unsigned char KEY_Scan(void)
{
    if (KEY_1 == 0)
    {
        Delay_ms(KEY_DEBOUNCE_MS);  /* 首次读到低电平，先等抖动结束再确认 */
        if (KEY_1 == 0)
        {
            while (KEY_1 == 0)      /* 等待松手，否则一次按压会被反复识别 */
            {
                ;
            }
            Delay_ms(KEY_DEBOUNCE_MS);  /* 松手瞬间同样有抖动，再消抖一次 */
            return KEY_VALUE_K1;
        }
    }

    return KEY_VALUE_NONE;
}
