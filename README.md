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
| 02-按键 | ⏳ 待开始 | 按键检测与消抖 |
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
├── 01-LED/          # LED控制（点亮、闪烁、流水灯）
├── Keil project/    # Keil工程文件（原始代码）
│   ├── 1-1点亮一个LED/
│   ├── 1-2LED闪烁/
│   └── 1-3LED流水灯/   ← 含3种实现方法
├── notes/           # 📝 学习笔记（按主题分类）
│   ├── README.md    ← 笔记索引
│   ├── LED.md
│   ├── 按键.md
│   ├── 模块原理图.md
│   ├── 工具库.md
│   └── 学习画像.md
├── raw_logs/        # 📋 DeepSeek原始聊天记录
├── 02-按键/         # （待开始）
├── 03-数码管/       # （待开始）
└── docs/            # 参考文档
```

## 01-LED 实验汇总

| 实验 | Keil工程 | 知识点 | 代码文件 |
|:---|:---|:---|:---|
| 1-1 点亮LED | `Keil project/1-1点亮一个LED/` | `sbit`、单引脚控制 | [main.c](Keil%20project/1-1点亮一个LED/main.c) |
| 1-2 LED闪烁 | `Keil project/1-2LED闪烁/` | 整组P2赋值、延时函数 | [main.c](Keil%20project/1-2LED闪烁/main.c) |
| 1-3 流水灯 | `Keil project/1-3LED流水灯/` | 手写移位、`_crol_`、`typedef` | [3个版本](Keil%20project/1-3LED流水灯/) |

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
