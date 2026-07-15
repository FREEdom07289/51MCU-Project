#include <REGX52.H>       // Keil 8051 系列单片机头文件，定义特殊功能寄存器
#include <INTRINS.H>       // Keil 内联函数头文件，用于 _crol_、_cror_ 等操作

typedef unsigned int u16;  // 对系统默认数据类型进行重定义，便于阅读
typedef unsigned char u8;  // 将 unsigned char 重命名为 u8

#define LED_PORT    P2      // 使用宏定义 LED 端口为 P2

// 简单延时函数，参数 ten_us 控制空循环次数
void delay_10us(u16 ten_us)
{
    while (ten_us--);
}
void main()
{
    u8 i = 0;                    // 循环变量，用于控制移位次数

    LED_PORT = ~0x01;             // 初始点亮最低位 LED（P2.0 输出低电平）
    delay_10us(50000);            // 延时，保持初始灯位状态
    while (1)
    {
		//方法1：使用移位+循环实现流水灯
//		for(i=0;i<8;i++)
//		{
//			LED_PORT=~(0x01<<i);	//将1右移i位，然后取反将结果赋值到LED_PORT
//			delay_10us(50000);
//		}
		
        // 方法2：使用循环 + _crol_ 或 _cror_ 函数实现流水灯
        for (i = 0; i < 7; i++)   // 向左循环移动 LED 灯图案
        {
            LED_PORT = _crol_(LED_PORT, 1);  // 循环左移 1 位
            delay_10us(50000);
        }
        for (i = 0; i < 7; i++)   // 向右循环移动 LED 灯图案
        {
            LED_PORT = _cror_(LED_PORT, 1);  // 循环右移 1 位
            delay_10us(50000);
        }
    }
}
