/**
 * @file    Delay.c
 * @brief   软件延时模块，基于空循环实现毫秒级延时
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    晶振 11.0592MHz，内层空循环 110 次实测约 1ms
 *          依赖模块：无
 *          修改记录：
 *            V1.0 2026-11-14 初版，统一各 LED 实验里各自的延时写法
 */
#include "Delay.h"

/* ==================== 私有宏 ==================== */

#define DELAY_LOOP_CNT  110     /* 1ms 对应的内层空循环次数，11.0592MHz 下实测标定 */

/* ==================== 对外接口实现 ==================== */

/**
 * @brief  毫秒级软件延时
 * @param  Ms 延时时间，单位毫秒，取值 0 ~ 65535
 * @retval None
 * @note   阻塞式延时，占用 CPU 空转，禁止在中断服务函数中调用
 */
void Delay(unsigned int Ms)
{
    unsigned int i, j;

    for (i = Ms; i > 0; i--)
    {
        for (j = DELAY_LOOP_CNT; j > 0; j--);
    }
}
