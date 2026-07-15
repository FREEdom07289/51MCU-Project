# 01-点亮LED

> 单片机第一课：点亮第一个LED

## 实验目标

理解 `sbit` 位定义和低电平驱动原理，让 P2.0 引脚输出低电平点亮 D1。

## 知识点

| 知识点 | 说明 |
|:---|:---|
| `sbit LED1 = P2^0` | Keil C51 位寻址关键字，单独定义一个引脚变量 |
| `LED1 = 0` | 输出低电平（0V），电流灌入单片机 → LED亮 |
| `while(1)` | 死循环，让程序停住不跑飞 |
| `REGX52.H` | STC89C52 专用头文件 |

## 文件说明

| 文件 | 说明 |
|:---|:---|
| [main.c](main.c) | 点亮D1（P2.0）的源码 |
| `project.uvproj` | Keil uVision5 工程文件 |

## 硬件连接

- LED D1 阳极 → VCC（+5V，经R1限流）
- LED D1 阴极 → P2.0
- **低电平（0）点亮，高电平（1）熄灭**

## 核心代码

```c
#include <REGX52.H>
sbit LED1 = P2^0;

void main()
{
    LED1 = 0;    // P2.0输出低电平，点亮D1
    while(1);    // 程序停在此处
}
```

---

📖 详细笔记：[notes/LED.md](../../notes/LED.md)
