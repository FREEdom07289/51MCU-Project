/**
 * @file    Delay.c
 * @brief   延时模块，提供毫秒级软件延时
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-11
 * @note    依赖：无
 *          修改记录：
 *            V1.0 2026-11-11 从原 LCD1602/main.c 拆分为独立模块
 */

#include "Delay.h"

/* ==================== 对外接口实现 ==================== */

/**
 * @brief  软件延时，约 ms 毫秒
 * @param  ms 延时时间，单位 ms
 * @retval None
 * @note   内层空循环 120 次约 1ms，换晶振后需重新标定；
 *         调用期间 CPU 被完全占用，长延时请改用定时器
 */
void Delay_ms(unsigned int ms)
{
    unsigned int i;
    unsigned int j;

    for (i = 0; i < ms; i++)
    {
        for (j = 0; j < 120; j++)
        {
            ;
        }
    }
}
