/*
 * LED点灯实验 - 普中A2开发板
 * 功能：LED0常亮（P2.0引脚）
 * 芯片：STC89C52RC
 * 晶振：11.0592MHz
 */

#include <reg52.h>  // 51单片机标准头文件

// 定义LED引脚
sbit LED = P2^0;    // LED0接在P2.0，低电平点亮

void main()
{
    while(1)
    {
        LED = 0;    // 输出低电平，点亮LED0
    }
}
