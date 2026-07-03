#include <reg52.h>
#include <intrins.h>   // 用来调用 _crol_（循环左移）

// 延时函数（11.0592MHz下，约延时 t 毫秒）
void delay_ms(unsigned int t) {
    unsigned int i, j;
    for(i = t; i > 0; i--)
        for(j = 110; j > 0; j--);
}

void main() {
    unsigned char i;          // 循环计数（0~6，共7步）
    
    while(1) {
        unsigned char x = 0xFC;   // 1111 1100 → 只有P2.0和P2.1是0（D1、D2亮）
        
        // ① 为什么只循环7次，而不是8次？
        // 因为0xFC循环左移7次后变成0x3F（0011 1111），对应D7、D8亮。
        // 如果再移第8次，就变成0x7F（只有一个灯亮），破坏了“双灯”模式。
        for(i = 0; i < 7; i++) {
            P2 = x;          // 输出当前图案
            delay_ms(200);         // 停留200ms，看清位置
            
            x = _crol_(x, 1);  // 循环左移1位（两个0同时向高位移动）
        }
        // ② 跑完7步后，跳出for循环，回到while(1)开头，
        //    x重新被赋值为0xFC，实现“从头开始”的无限循环。
    }
}