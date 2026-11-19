/**
 * @file    Delay.c
 * @brief   延时模块，基于空循环实现 10us 级延时
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    晶振 11.0592MHz，1 个单位约 10us
 *          依赖模块：无
 *          修改记录：
 *            V1.0 2026-11-14 从蜂鸣器单文件代码中拆出延时函数
 */
#include "Delay.h"

/* ==================== 对外接口实现 ==================== */

/**
 * @brief  10us 级软件延时
 * @param  TenUs 延时单位数，取值 1 ~ 65535，约等于 TenUs × 10us
 * @retval None
 * @note   阻塞式延时，禁止在中断服务函数中调用
 */
void Delay_10us(unsigned int TenUs)
{
    while (TenUs--);
}
