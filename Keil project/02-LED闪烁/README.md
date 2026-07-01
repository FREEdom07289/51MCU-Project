# 02-LED闪烁

> 引入软件延时，让LED"动"起来

## 实验目标

理解延时函数的作用，掌握整组 P2 赋值同时控制 8 个 LED 闪烁。

## 知识点

| 知识点 | 说明 |
|:---|:---|
| `P2 = 0x00` | 8个引脚全输出低电平 → 8灯全亮 |
| `P2 = 0xFF` | 8个引脚全输出高电平 → 8灯全灭 |
| `Delay(unsigned int t)` | 双循环软件延时，`t=500` ≈ 500ms |
| `while(1)` | 主循环，让闪烁永远持续 |

## 文件说明

| 文件 | 说明 |
|:---|:---|
| [main.c](main.c) | LED闪烁源码（含注释掉的早期单灯版本） |
| [STARTUP.A51](STARTUP.A51) | Keil 启动文件（初始化 RAM、跳转 main） |
| `project.uvproj` | Keil uVision5 工程文件 |

## 延时函数原理

```c
void Delay(unsigned int t)
{
    unsigned int i, j;
    for(i = t; i > 0; i--)       // 外层循环 t 次
        for(j = 110; j > 0; j--); // 内层110次 ≈ 1ms（11.0592MHz经验值）
}
```

不加延时的话，CPU每微秒执行一条指令，灯亮灭切换太快（百万分之一秒），人眼看不出来。

## 核心代码

```c
void main(void)
{
    while(1)
    {
        P2 = 0x00;   // 全亮
        Delay(500);  // 保持500ms
        P2 = 0xFF;   // 全灭
        Delay(500);  // 保持500ms
    }
}
```

---

📖 详细笔记：[notes/LED.md](../../notes/LED.md)
