/**
 * @file    Delay.c
 * @brief   软件延时模块，基于空循环实现 10us 级延时
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    循环次数与实际时间未做精确标定，仅用于对时序要求不严的等待
 *          依赖模块：无
 *          修改记录：
 *            V1.0 2026-11-14 初版，统一各 LED 实验里各自的延时写法
 */
#include "Delay.h"

/* ==================== 对外接口实现 ==================== */

/**
 * @brief  10us 级软件延时
 * @param  TenUs 延时时间，单位 10us，取值 0 ~ 65535
 * @retval None
 * @note   仅用于对时序要求不严的等待，不能作为精确计时使用
 */
void Delay_10us(unsigned int TenUs)
{
    while (TenUs--);
}
