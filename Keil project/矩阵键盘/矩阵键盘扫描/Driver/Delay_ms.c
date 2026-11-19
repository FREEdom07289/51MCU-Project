/**
 * @file    Delay_ms.c
 * @brief  毫秒级延时函数
 * @param  ms 延时时间，单位毫秒
 * @retval None
 * @date    2026-11-14  
 * @note   11.0592MHz 晶振
 *        
 */
void Delay_ms(unsigned char ms)	//@11.0592MHz
{
	unsigned char data i, j;
    while(ms)
	_nop_();
	i = 2;
	j = 199;
    {   
        do
	    {
		    while (--j);
	    }   
            while (--i);
    }
    ms--;
}
