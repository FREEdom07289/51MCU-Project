#include <REGX52.H>
sbit Beep = P2^5;

/* Freq表：扩展出低音区（稻香间奏需要低音）*/
/* 0休 1=C4..7=B4  8=C5..14=B5(高音)  15=C3..21=B3(低音) */
unsigned int code Freq[22] = {0,
    262,294,330,349,392,440,494,          /* 中音 1~7 */
    523,587,659,698,784,880,988,          /* 高音 1~7 */
    131,147,165,175,196,220,247 };        /* 低音 1~7 */

void Delay(unsigned int n){ while(n--); }
void PlayFreq(unsigned int freq, unsigned int ms){
    unsigned long cyc = (unsigned long)freq * ms / 1000;
    unsigned int half = 250000UL / freq;
    if(freq == 0){ Delay(500); return; }     // 休止
    while(cyc--){ Beep = ~Beep; Delay(half/10); }  // 时间常数按你晶振调
}
void PlayN(unsigned char n, unsigned char b){ PlayFreq(Freq[n], (unsigned int)b*180); }

/*稻香间奏: 高1 高3 高5 休 低2 低7 低5 ×2 | 高1 低5 高1 低5 | 高1─*/
unsigned char code Melody[][2] = {
    {8,2},{10,2},{12,2},{0,2},{16,2},{21,2},{19,3},
    {8,2},{10,2},{12,2},{0,2},{16,2},{21,2},{19,3},
    {8,2},{19,2},{8,2},{19,2},
    {8,6},
    {0,0}
};
void main(void){
    unsigned char i;
    while(1){
        for(i=0; Melody[i][0]!=0 || Melody[i][1]!=0; i++)
            PlayN(Melody[i][0], Melody[i][1]);
        Delay(30000);
    }
}