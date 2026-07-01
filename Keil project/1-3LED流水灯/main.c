#include <REGX52.H>
#include <INTRINS.H>

typedef unsigned int u16;	//对系统默认数据类型进行重定义
typedef unsigned char u8;

#define LED_PORT	P2	//使用宏定义P2端口

void delay_10us(u16 ten_us)
{
	while(ten_us--);	
}
void main()
{	
   	u8 i=0;

	LED_PORT=~0x01;
	delay_10us(50000);
	while(1)
	{
		//方法1：使用移位+循环实现流水灯
//		for(i=0;i<8;i++)
//		{
//			LED_PORT=~(0x01<<i);	//将1右移i位，然后取反将结果赋值到LED_PORT
//			delay_10us(50000);
//		}
		
		//方法2：使用循环+_crol_或_cror_函数实现流水灯
		for(i=0;i<7;i++)	 //将led左移一位
		{									  
			LED_PORT=_crol_(LED_PORT,1);
			delay_10us(50000); 	
		}
		for(i=0;i<7;i++)	//将led右移一位
		{
			LED_PORT=_cror_(LED_PORT,1);
			delay_10us(50000);	
		}	
	}		
}