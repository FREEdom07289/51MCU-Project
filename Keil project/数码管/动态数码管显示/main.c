#include <REGX52.H>

typedef unsigned char u8;
typedef unsigned int u16;

// 共阴极段码表：0~F，'-'，灭
u8 code SMG_Code[] = {
    0x3F, 0x06, 0x5B, 0x4F,  // 0 1 2 3
    0x66, 0x6D, 0x7D, 0x07,  // 4 5 6 7
    0x7F, 0x6F, 0x77, 0x7C,  // 8 9 A b
    0x39, 0x5E, 0x79, 0x71,  // C d E F
    0x40, 0x00               // 16='-' 17=灭
};

u8 SMG_Buf[8] = {0, 1, 2, 3, 4, 5, 6, 7};  // 显示缓冲区
u8 scan_pos = 0;

// 单独点亮某一位数码管（可用于单独测试）
void SMG_Display(u8 pos, u8 dat) {
    P0 = 0x00;                         // 先消影，避免段选残留
    P2 = (P2 & 0xE3) | ((7 - pos) << 2);  // 选择位，倒序映射，符合板载显示顺序
    P0 = SMG_Code[dat];                // 送段码
}

// 扫描函数：在定时器中断中周期性调用，每次切换一位
void SMG_Scan(void) {
    P0 = 0x00;                         // 先关断当前段码，防止重影
    P2 = (P2 & 0xE3) | ((7 - scan_pos) << 2); // 选通当前位
    P0 = SMG_Code[SMG_Buf[scan_pos]];  // 送段码
    scan_pos++;
    if (scan_pos >= 8) {
        scan_pos = 0;
    }
}

void Timer0_Init(void) {
    TMOD = 0x01;                // 定时器0：方式1，16位定时
    TH0 = (65536 - 1000) / 256; // 1ms 定时初值（以12MHz晶振计）
    TL0 = (65536 - 1000) % 256;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
}

void main(void) {
    u8 i;
    // 先写入显示缓冲区
    for (i = 0; i < 8; i++) {
        SMG_Buf[i] = i;
    }

    Timer0_Init();

    while (1) {
        // 主循环中可继续处理其他任务
    }
}
// 定时器0中断服务函数，每1ms调用一次
void Timer0_ISR(void) interrupt 1 {
    TH0 = (65536 - 1000) / 256;
    TL0 = (65536 - 1000) % 256;
    SMG_Scan();
}
// 以上代码实现了一个8位共阴极数码管的动态扫描显示，使用定时器0中断每1ms刷新一位数码管。