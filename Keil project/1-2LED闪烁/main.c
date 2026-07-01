#include <REGX52.H>
//延时函数
void Delay(unsigned int t)
{
    unsigned int i, j;
    for(i = t; i > 0; i--)
    {
        for(j = 110; j > 0; j--);
    }
}
void main(void)
{
    while(1)
    {
        P2 = 0x00; // 点亮LED（LED连接在P2.0-P2.7）
        Delay(500); // 延时500ms
        P2 = 0xFF; // 熄灭LED
        Delay(500); // 延时500ms
    }
}




/*
// 定义LED引脚，通常开发板上的LED连接到P2.0
sbit LED = P2^0;

// 简单延时函数，约为几百毫秒，供LED闪烁使用
void Delay(void)
{
    unsigned int i, j;
    for(i = 0; i < 200; i++)
    {
        for(j = 0; j < 200; j++);
    }
}

void main(void)
{
    // 初始化LED为熄灭状态（高电平或低电平取决于硬件）
    LED = 1; // 通常LED为低电平点亮，如果实际相反请改为LED = 0

    while(1)
    {
        LED = 0;   // 点亮LED
        Delay();   // 延时
        LED = 1;   // 熄灭LED
        Delay();   // 延时
    }
}
*/