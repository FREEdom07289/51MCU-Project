/**
 * @file    main.c
 * @brief   LED 实验 01：点亮 D1（P2.0）
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    硬件：STC89C52 + 8 位 LED（P2.0 ~ P2.7，低电平点亮）
 *          现象：上电后 D1 常亮，其余 LED 熄灭
 *          修改记录：
 *            V1.0 2026-11-14 按模块化规范重组，P2 口操作移入 Driver/LED.c
 */
#include <REGX52.H>
#include "LED.h"

/* ==================== 主函数 ==================== */

void main(void)
{
    LED_Init();                 /* 先全部熄灭，不依赖上电复位后的端口默认值 */
    LED_OnOne(0);               /* 点亮编号 0，即 D1 */

    while (1)
    {
        /* 保持点亮，主循环无需处理 */
    }
}
