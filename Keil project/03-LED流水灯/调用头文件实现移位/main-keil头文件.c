#include <reg52.h>      // 包含 8051 单片机特殊功能寄存器和端口定义
#include <intrins.h>     // 包含 Keil 内联函数，例如循环移位函数

// 延时函数，time 越大延时越长
void delay(unsigned int time)
{
    unsigned int i, j;
    for (i = 0; i < time; i++)
        for (j = 0; j < 120; j++);
}
/*
//单向移位，从P2.0到P2.7，循环移位
void main(void)
{
    unsigned char x = 0xFE; // 初始移位数据：1111 1110，用于控制 P2 口 LED
    while (1)
    {
        P2 = x;               // 输出当前移位结果到 P2 口
        delay(500);           // 延时，便于观察 LED 灯光移动
        x = _crol_(x, 1);     // 循环左移 1 位，实现环形流水效果
    }
}*/

// 双向移位，从 P2.0 到 P2.7，循环移位
void main(void)
{
    unsigned char x = 0xFE; // 初始移位数据：1111 1110，用于控制 P2 口 LED
    while (1)
    {
        unsigned char i;
        for (i = 0; i < 7; i++) // 循环左移 7 次
        {
            P2 = x;               // 输出当前移位结果到 P2 口
            delay(500);           // 延时，便于观察 LED 灯光移动
            x = _crol_(x, 1);     // 循环左移 1 位，实现环形流水效果
        }
        for (i = 0; i < 7; i++) // 循环右移 7 次
        {
            P2 = x;               // 输出当前移位结果到 P2 口
            delay(500);           // 延时，便于观察 LED 灯光移动
            x = _cror_(x, 1);     // 循环右移 1 位，实现环形流水效果
        }
    }
}
