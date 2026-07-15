/*
 * 05-按键控制LED流水灯 - 普中A2开发板
 * 功能：K1切换LED流水方向 / K2启停流水灯
 * 作者：freedom
 * 日期：2026-07-08
 *
 * 硬件连接：
 *   LED（8个） → P2.0 ~ P2.7（低电平点亮）
 *   独立按键K1 → P3.0（按下为低电平）
 *   独立按键K2 → P3.1（按下为低电平）
 */

#include <REGX52.H>
#include <INTRINS.H>

// ===== 类型重定义 =====
typedef unsigned int u16;
typedef unsigned char u8;

// ===== 引脚定义 =====
#define LED_PORT P2
sbit KEY1 = P3^0;   // K1：切换流水方向
sbit KEY2 = P3^1;   // K2：启停流水灯

// ===== 全局变量 =====
u8 direction = 0;   // 0=左移(D1→D8)，1=右移(D8→D1)
u8 running   = 1;   // 1=流水运行中，0=暂停

// ===== 函数声明 =====
void delay_ms(u16 ms);          // 毫秒延时
u8   key_scan(void);            // 按键扫描（带消抖），返回键值

// ===== 主函数 =====
void main()
{
    u8 led = 0xFE;              // 初始：1111 1110 → 只有D1亮

    while(1)
    {
        u8 key = key_scan();    // 扫描按键

        // ① K1按下 → 切换流水方向
        if(key == 1)
        {
            direction = !direction;   // 方向取反
        }

        // ② K2按下 → 启停流水灯
        if(key == 2)
        {
            running = !running;       // 运行状态取反
        }

        // ③ 如果处于运行状态，执行流水灯
        if(running)
        {
            LED_PORT = led;
            delay_ms(200);            // 每步停留200ms

            if(direction == 0)        // 左移：D1 → D8
            {
                led = _crol_(led, 1);
            }
            else                      // 右移：D8 → D1
            {
                led = _cror_(led, 1);
            }
        }
    }
}

// ===== 软件延时函数（约1ms × 参数值 @11.0592MHz） =====
void delay_ms(u16 ms)
{
    u16 i, j;
    for(i = ms; i > 0; i--)
        for(j = 110; j > 0; j--);
}

// ===== 按键扫描函数（独立按键，带软件消抖） =====
u8 key_scan(void)
{
    // ① 检测K1是否按下（低电平有效）
    if(KEY1 == 0)
    {
        delay_ms(20);           // ② 延时20ms消抖
        if(KEY1 == 0)           // ③ 再次确认按键仍按下
        {
            while(KEY1 == 0);   // ④ 等待按键松开（防连击）
            return 1;           // 返回键值1
        }
    }

    // 检测K2是否按下（同上流程）
    if(KEY2 == 0)
    {
        delay_ms(20);
        if(KEY2 == 0)
        {
            while(KEY2 == 0);
            return 2;           // 返回键值2
        }
    }

    return 0;                   // 无按键按下
}
