/**
 * @file    SMG.c
 * @brief   数码管驱动模块，提供段码查表与静态字符显示
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    硬件引脚：P0.0 ~ P0.7 经 74HC245 接数码管 a ~ dp，共阴数码管高电平点亮
 *          依赖模块：无
 *          修改记录：
 *            V1.0 2026-11-14 从静态数码管单文件代码中拆出段码表与段选输出
 */
#include "SMG.h"

/* ==================== 私有变量 ==================== */

static unsigned char code SMG_Code[16] = {
    0x3F, 0x06, 0x5B, 0x4F,     /* 0 1 2 3 */
    0x66, 0x6D, 0x7D, 0x07,     /* 4 5 6 7 */
    0x7F, 0x6F, 0x77, 0x7C,     /* 8 9 A b */
    0x39, 0x5E, 0x79, 0x71      /* C d E F */
};

/* ==================== 对外接口实现 ==================== */

/**
 * @brief  在数码管上静态显示一个字符
 * @param  Index 段码表下标，取值 0 ~ 15，依次对应 0 ~ 9、A、b、C、d、E、F
 * @retval None
 * @note   本实验只驱动段选，位选由 74HC138 默认状态决定，不在此处切换
 */
void SMG_ShowChar(unsigned char Index)
{
    SMG_SEG_PORT = SMG_Code[Index];
}
