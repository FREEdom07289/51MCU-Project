/**
 * @file    SMG.c
 * @brief   数码管驱动模块，提供位选切换、段码输出与逐位扫描
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-14
 * @note    硬件引脚：P0 段选（a ~ dp），P2.2 ~ P2.4 接 74HC138 位选
 *          依赖模块：无
 *          修改记录：
 *            V1.0 2026-11-14 从动态数码管单文件代码中拆出扫描驱动
 */
#include "SMG.h"

/* ==================== 私有宏与变量 ==================== */

#define SMG_SEG_PORT    P0      /* 段选端口，bit0 ~ bit7 依次对应 a ~ dp */
#define SMG_POS_PORT    P2      /* 位选端口，P2.2 ~ P2.4 接 74HC138 的 A0 ~ A2 */
#define SMG_POS_MASK    0xE3    /* 只清 P2.2 ~ P2.4，保留 LED 等复用引脚 */

/* 显示缓冲区：AT89C52 无外部 RAM，只能放片内 data/idata */
volatile unsigned char SMG_Buf[SMG_NUM] = {0, 1, 2, 3, 4, 5, 6, 7};

/* 段码表：0 ~ 9、A、b、C、d、E、F，共阴数码管高电平点亮 */
static unsigned char code SMG_Code[16] = {
    0x3F, 0x06, 0x5B, 0x4F,     /* 0 1 2 3 */
    0x66, 0x6D, 0x7D, 0x07,     /* 4 5 6 7 */
    0x7F, 0x6F, 0x77, 0x7C,     /* 8 9 A b */
    0x39, 0x5E, 0x79, 0x71      /* C d E F */
};

static unsigned char ScanPos = 0;   /* 当前扫描位，0 对应最右侧数码管 */

/* ==================== 对外接口实现 ==================== */

/**
 * @brief  扫描并刷新一位数码管
 * @retval None
 * @note   由主循环按 1ms 周期调用；先关段码消影，再切换位选、送新段码
 */
void SMG_Scan(void)
{
    SMG_SEG_PORT = 0x00;                                    /* 关段码，消除上一位残影 */
    SMG_POS_PORT = (SMG_POS_PORT & SMG_POS_MASK) | ((7 - ScanPos) << 2);  /* 位选倒序映射 */
    SMG_SEG_PORT = SMG_Code[SMG_Buf[ScanPos]];              /* 送出该位段码 */

    if (++ScanPos >= SMG_NUM)
    {
        ScanPos = 0;
    }
}
