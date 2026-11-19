/**
 * @file    KEY.c
 * @brief   独立按键驱动模块，提供单次触发的按键扫描
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    硬件引脚（普中 A2 独立按键模块）：K1 -> P3.1，K2 -> P3.0，K3 -> P3.2
 *          依赖模块：Delay.c（提供 10ms 消抖延时）
 *          修改记录：
 *            V1.0 2026-11-14 从 LCD1602 单文件代码中拆出按键扫描
 */
#include <REGX52.H>
#include "KEY.h"
#include "Delay.h"

/* ==================== 私有宏与引脚 ==================== */

sbit KEY_PIN_K1 = P3^1;
sbit KEY_PIN_K2 = P3^0;
sbit KEY_PIN_K3 = P3^2;

#define KEY_DEBOUNCE_MS 10      /* 消抖延时，单位 ms */

static unsigned char KeyReleased = 1;   /* 1=所有按键已松开，允许下一次检测 */

/* ==================== 对外接口实现 ==================== */

/**
 * @brief  扫描独立按键
 * @retval KEY_VALUE_NONE 无按键按下
 * @retval KEY_VALUE_K1    K1 按下
 * @retval KEY_VALUE_K2    K2 按下
 * @retval KEY_VALUE_K3    K3 按下
 * @note   单次触发：按住不放只返回一次，松开后才允许下一次
 */
unsigned char KEY_Scan(void)
{
    if (KeyReleased && (KEY_PIN_K1 == 0 || KEY_PIN_K2 == 0 || KEY_PIN_K3 == 0))
    {
        Delay_ms(KEY_DEBOUNCE_MS);      /* 避开按下瞬间的抖动 */
        KeyReleased = 0;

        if (KEY_PIN_K1 == 0)
        {
            return KEY_VALUE_K1;
        }
        if (KEY_PIN_K2 == 0)
        {
            return KEY_VALUE_K2;
        }
        if (KEY_PIN_K3 == 0)
        {
            return KEY_VALUE_K3;
        }
    }
    else if (KEY_PIN_K1 == 1 && KEY_PIN_K2 == 1 && KEY_PIN_K3 == 1)
    {
        KeyReleased = 1;                /* 全部松开，允许下一次检测 */
    }

    return KEY_VALUE_NONE;
}
