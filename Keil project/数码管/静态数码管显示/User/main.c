/**
 * @file    main.c
 * @brief   数码管实验：静态显示字符 A
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    硬件：STC89C52RC + 共阴数码管（P0 段选，74HC245 驱动，74HC138 位选）
 *          现象：数码管静态显示字符 A
 *          修改记录：
 *            V1.0 2026-11-14 按模块化规范拆分 Driver/User，段码表移入 Driver/SMG.c
 */
#include "SMG.h"

/* ==================== 主函数 ==================== */

void main(void)
{
    SMG_ShowChar(SMG_CHAR_A);

    while (1)
    {
        /* 静态显示只需保持段选输出，主循环空闲 */
    }
}
