# 51单片机学习项目

> 基于普中A2开发板，跟随江科大视频系统学习。使用 DeepSeek AI 辅助整理笔记。

## 开发环境
- **芯片**：STC89C52RC
- **晶振**：11.0592MHz
- **IDE**：Keil uVision + VSCode
- **下载工具**：STC-ISP
- **笔记系统**：Obsidian（库路径：`D:\obsidian\qisimiaoxiang\奇思妙想`）

## 学习进度

| 模块 | 状态 | 说明 |
|------|------|------|
| 01-LED | ✅ 已完成 | 点亮LED + LED闪烁 + 流水灯（3种方法） |
| 02-按键 | 🔄 进行中 | 按键检测初版代码（含典型错误分析） |
| 03-数码管 | ⏳ 待开始 | 数码管显示 |
| 04-定时器 | ⏳ 待开始 | 定时器/计数器 |
| 05-中断 | ⏳ 待开始 | 中断系统 |
| 06-串口通信 | ⏳ 待开始 | UART串口通信 |
| 07-I2C-SPI | ⏳ 待开始 | I2C/SPI总线 |
| 08-ADC | ⏳ 待开始 | 模数转换 |
| 09-LCD显示 | ⏳ 待开始 | LCD1602显示 |

## 目录结构
```
普中51单片机/
├── .gitignore        # 排除Keil构建产物
├── README.md         # 项目主页
├── Keil project/     # 🔧 Keil工程（实验源码）
│   ├── 01-点亮LED/    ← 单LED点亮
│   ├── 02-LED闪烁/    ← 8灯同步闪烁
│   ├── 03-LED流水灯/   ← 3种方法（3个独立工程）
│   │   ├── 手写移位/
│   │   ├── 调用头文件实现移位/
│   │   └── 双向移位/
│   ├── LED练习部分/
│   │   ├── 练习1/      ← 8灯亮1s灭0.5s
│   │   └── 练习2/      ← 双灯流水灯
│   └── 按键/           ← 按键初版（含x=P2错误分析）
├── notes/            # 📝 学习笔记（按主题分类）
│   ├── README.md     ← 笔记索引
│   ├── LED.md
│   ├── 按键.md
│   ├── 模块原理图.md
│   ├── 工具库.md
│   ├── 学习画像.md
│   ├── Obsidian_51单片机LED笔记.md    ← Obsidian版（双链+标签）
│   └── GitHub_LED实验完整手册.md      ← GitHub版（[TOC]+故障排查附录）
├── raw_logs/         # 📋 DeepSeek原始聊天记录
└── docs/             # 参考文档（原理图PDF等）
```

## LED 实验汇总

| 实验 | 路径 | 知识点 | 源码 |
|:---|:---|:---|:---|
| 01-点亮LED | `Keil project/01-点亮LED/` | `sbit`、单引脚控制、低电平驱动 | [main.c](Keil%20project/01-点亮LED/main.c) |
| 02-LED闪烁 | `Keil project/02-LED闪烁/` | 整组P2赋值、延时函数、`while(1)` | [main.c](Keil%20project/02-LED闪烁/main.c) |
| 03-流水灯(A) | `Keil project/03-LED流水灯/手写移位/` | 手写循环左移+右移位运算 | [手写移位.c](Keil%20project/03-LED流水灯/手写移位/main-手写移位.c) |
| 03-流水灯(B) | `Keil project/03-LED流水灯/调用头文件实现移位/` | `_crol_`/`_cror_` 双向移位 | [头文件.c](Keil%20project/03-LED流水灯/调用头文件实现移位/main-keil头文件.c) |
| 03-流水灯(C) | `Keil project/03-LED流水灯/双向移位/` | `typedef`+`#define` 工程风格 | [main.c](Keil%20project/03-LED流水灯/双向移位/main.c) |
| 练习1 | `Keil project/LED练习部分/练习1/` | 8灯亮1s灭0.5s（修正版） | [main.c](Keil%20project/LED练习部分/练习1/main.c) |
| 练习2 | `Keil project/LED练习部分/练习2/` | 双灯流水灯 `0xFC`+`_crol_` | [main.c](Keil%20project/LED练习部分/练习2/main.c) |

> 📖 详细笔记：[notes/LED.md](notes/LED.md)

## 笔记系统

所有学习笔记存放在 [notes/](notes/) 目录，按主题分类：

- [[LED]](notes/LED.md) — LED硬件原理、sbit、流水灯、移位函数（✅ 完整）
- [[按键]](notes/按键.md) — 按键消抖原理与模板代码（⚠️ 待补充）
- [[模块原理图]](notes/模块原理图.md) — 普中A2各模块引脚连接（⚠️ 待补充）
- [[工具库]](notes/工具库.md) — REGX52.H、intrins.h、typedef、延时函数（✅ 完整）
- [[学习画像]](notes/学习画像.md) — 学习背景与目标（⚠️ 待补充）

> 笔记同时同步到 Obsidian 库：`04_实验与项目/51单片机学习笔记/`

## 作者
- **freedom** (GitHub: [@FREEdom07289](https://github.com/FREEdom07289))
- 大一电子信息工程专业
