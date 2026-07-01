#include <reg52.h>      // 包含 8051 单片机寄存器定义和特殊功能寄存器声明

// 延时函数，循环次数与 time 参数成正比
void delay(unsigned int time)
{
    unsigned int i, j;
    for (i = 0; i < time; i++)
        for (j = 0; j < 120; j++);
}

void main(void)
{
    unsigned char x = 0xFE;  // 初始移位数据：1111 1110，用于控制 P2 口 LED
    while (1)
    {
        P2 = x;               // 输出当前数据到 P2 口，控制 LED 灯状态
        delay(500);           // 延时，让 LED 灯变化可见
        x = (x << 1) | (x >> 7); // 循环左移 1 位，最低位补回最高位，实现环形移动
    }
}   