/*
 静态数码管显示 - 普中A2开发板 
作者：freedom
日期：2026-07-15

*/
#include <REGX52.H>
typedef unsigned char u8;
typedef unsigned int u16;

#define SMG_A_DP_PORT P0          // 数码管段选口：P0 控制 a,b,c,d,e,f,g,dp
// 共阴数码管段码：高电平点亮对应段
u8 gsmg_code[16] = {
    0x3f, // 0 -> a b c d e f
    0x06, // 1 -> b c
    0x5b, // 2 -> a b d e g
    0x4f, // 3 -> a b c d g
    0x66, // 4 -> b c f g
    0x6d, // 5 -> a c d f g
    0x7d, // 6 -> a c d e f g
    0x07, // 7 -> a b c
    0x7f, // 8 -> a b c d e f g
    0x6f, // 9 -> a b c d f g
    0x77, // A -> a b c e f g
    0x7c, // b -> c d e f g
    0x39, // C -> a d e f
    0x5e, // d -> b c d e g
    0x79, // E -> a d e f g
    0x71  // F -> a e f g
};

void main(void)
{
    // 选择显示字符 A（数组下标 10）
    // 如果要显示数字 0~9，可直接改成 gsmg_code[0] ~ gsmg_code[9]
    SMG_A_DP_PORT = gsmg_code[10];

    while(1)
    {
        // 静态显示实验只需保持段选输出
        // 若要扩展为多位动态扫描，需要额外控制位选引脚
    }
}
/*
当前板子实际连接说明：
- P0 作为数码管段选输出，到 74HC245 后驱动 a,b,c,d,e,f,g,dp。
- 74HC138 译码器输出 ~Y0~~Y7 作为数码管的位选信号。
- 本实验采用静态方式，仅让 SMG1 最左边的数码管保持选通。

普中A2 开发板特殊点：
- P2.2~P2.5 与 LED D3~D6 复用。
- 如果同时驱动 LED 和数码管，会出现引脚冲突。
- 练习数码管时，建议断开 LED 模块相关跳线帽，确保 P2 只有数码管位选用途。
*/