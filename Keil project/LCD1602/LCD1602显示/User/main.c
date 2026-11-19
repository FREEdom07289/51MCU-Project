/**
 * @file    main.c
 * @brief   LCD1602 实验：按键加减计数并显示
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    硬件：STC89C52RC + LCD1602 + 独立按键 K1/K2/K3
 *          现象：第一行显示 Count:，第二行显示 4 位计数值；
 *                K1 加 1，K2 减 1，K3 清零
 *          修改记录：
 *            V1.0 2026-11-14 按模块化规范拆分 Driver/System/User，
 *                            LCD 时序移入 Driver/LCD1602.c，按键扫描移入 Driver/KEY.c
 */
#include "LCD1602.h"
#include "KEY.h"

/* ==================== 私有变量 ==================== */

static unsigned int Count = 0;      /* 计数值，范围 0 ~ 9999 */

/* ==================== 主函数 ==================== */

void main(void)
{
    unsigned char Key;

    LCD1602_Init();                         /* 初始化必须在任何显示操作之前 */
    LCD1602_ShowString(1, 1, "Count:");
    LCD1602_ShowNum(2, 1, Count, 4);

    while (1)
    {
        Key = KEY_Scan();

        if (Key == KEY_VALUE_K1)
        {
            if (Count < 9999)               /* 防止 4 位显示溢出 */
            {
                Count++;
                LCD1602_ShowNum(2, 1, Count, 4);
            }
        }
        else if (Key == KEY_VALUE_K2)
        {
            if (Count > 0)
            {
                Count--;
                LCD1602_ShowNum(2, 1, Count, 4);
            }
        }
        else if (Key == KEY_VALUE_K3)
        {
            Count = 0;
            LCD1602_ShowNum(2, 1, Count, 4);
        }
    }
}
