#include <REGX52.H>
void delay(unsigned int t)
{
    int i,j;
    for(i=t;i>0;i--)
    {
        for(j=110;j>0;j--);
    }
}

void main(void)
{unsigned char x=P2;
    while(1)
    {
        x=0x00;
        delay(1000);
        x=0xFF;
        delay(500);
    }
}