#include <REGX52.H>

// 延时函数，参数 t 表示延时时间，单位为毫秒
void delay(unsigned int t)
{
    unsigned int i, j;
    for (i = t; i > 0; i--)
    {
        for (j = 110; j > 0; j--);
    }
}

void main(void)
{
    while (1)
    {
        P2 = 0x00;      // 8个灯全亮
        delay(1000);    // 延时1秒

        P2 = 0xFF;      // 8个灯全灭
        delay(500);     // 延时0.5秒
    }
}