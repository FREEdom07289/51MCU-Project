# 51单片机学习项目

> 基于普中A2开发板（STC89C52RC），跟随江科大视频系统学习。使用 AI 辅助整理笔记。

## 开发环境

- **芯片**：STC89C52RC
- **晶振**：11.0592MHz
- **IDE**：Keil uVision + VSCode
- **下载工具**：STC-ISP
- **笔记系统**：Obsidian（库路径：`D:\obsidian\qisimiaoxiang\奇思妙想`）

## 学习进度

| 模块 | 状态 | 完成日期 | 说明 |
|------|:---:|------|------|
| 01-LED | ✅ 完成 | 2026-07-03 | 点亮LED + LED闪烁 + 流水灯（3种方法）+ 2个练习 |
| 02-独立按键 | ✅ 完成 | 2026-07-25 | 消抖 + 方向切换/启停 + 亮灭翻转 + 二进制显示 + 移位（4个工程） |
| 03-蜂鸣器 | ✅ 完成 | 2026-09-24 | 有源蜂鸣器 + ULN2003D 驱动 |
| 04-数码管 | ✅ 完成 | 2026-09-24 | 静态显示（74HC245+74HC138）+ 动态扫描 |
| 05-LED点阵 | ✅ 完成 | 2026-09-24 | 74HC595 串转并 + 8×8 列扫描（显示心形） |
| 06-定时器 | ⏳ 待开始 | - | 定时器/计数器 |
| 07-中断 | ⏳ 待开始 | - | 中断系统 |
| 08-串口通信 | ⏳ 待开始 | - | UART串口通信 |
| 09-I2C-SPI | ⏳ 待开始 | - | I2C/SPI总线 |
| 10-ADC | ⏳ 待开始 | - | 模数转换 |
| 11-LCD显示 | ⏳ 待开始 | - | LCD1602显示 |

> 状态标记：✅ 完成 ｜ 🔄 进行中 ｜ ⏳ 待开始 ｜ ❌ 有问题待解决

## 目录结构

```
普中51单片机/
├── .gitignore        # 排除Keil构建产物
├── README.md         # 项目主页（你在这里）
├── Keil project/     # 🔧 Keil工程（实验源码）
│   ├── LED/              ← 点亮 / 闪烁 / 流水灯(3种) / 练习(2个)
│   ├── 按键/              ← 05~08 共 4 个独立按键工程
│   ├── 数码管/            ← 静态数码管显示 + 动态数码管显示
│   ├── 蜂鸣器/            ← 有源蜂鸣器驱动
│   └── LED点阵实验/       ← 74HC595 + 8×8 点阵（显示心形）
├── notes/            # 📝 学习笔记（Obsidian 主库的镜像快照）
│   ├── 00_索引/           ← README、51单片机MOC、总目录
│   ├── 01_入门准备/
│   ├── 02_编程基础/
│   ├── 03_基础外设/        ← LED、按键、蜂鸣器、数码管、LED点阵…
│   ├── 04_参考资料/        ← 模块原理图、工具库、学习画像
│   └── images/            ← 笔记配图
├── raw_logs/         # 📋 DeepSeek原始聊天记录
└── docs/             # 参考文档（原理图PDF等）
```

## LED 实验汇总

| 实验 | 路径 | 知识点 | 源码 |
|:---|:---|:---|:---|
| 01-点亮LED | `Keil project/LED/01-点亮LED/` | `sbit`、单引脚控制、低电平驱动 | [main.c](Keil%20project/LED/01-点亮LED/main.c) |
| 02-LED闪烁 | `Keil project/LED/02-LED闪烁/` | 整组P2赋值、延时函数、`while(1)` | [main.c](Keil%20project/LED/02-LED闪烁/main.c) |
| 03-流水灯(A) | `Keil project/LED/03-LED流水灯/手写移位/` | 手写循环左移+右移位运算 | [手写移位.c](Keil%20project/LED/03-LED流水灯/手写移位/main-手写移位.c) |
| 03-流水灯(B) | `Keil project/LED/03-LED流水灯/库函数移位/` | `_crol_`/`_cror_` 双向移位 | [头文件.c](Keil%20project/LED/03-LED流水灯/库函数移位/main-keil头文件.c) |
| 03-流水灯(C) | `Keil project/LED/03-LED流水灯/双向移位/` | `typedef`+`#define` 工程风格 | [main.c](Keil%20project/LED/03-LED流水灯/双向移位/main.c) |
| 练习1 | `Keil project/LED/04-LED练习/练习1/` | 8灯亮1s灭0.5s（修正版） | [main.c](Keil%20project/LED/04-LED练习/练习1/main.c) |
| 练习2 | `Keil project/LED/04-LED练习/练习2/` | 双灯流水灯 `0xFC`+`_crol_` | [main.c](Keil%20project/LED/04-LED练习/练习2/main.c) |

> 📖 详细笔记：[notes/03_基础外设/LED.md](notes/03_基础外设/LED.md)

## 独立按键实验

| 实验 | 路径 | 功能 | 源码 |
|:---|:---|:---|:---|
| 05-方向+启停 | `Keil project/按键/05-独立按键控制流水灯方向和启停/` | K1 启停、K2 切方向 | [main.c](Keil%20project/按键/05-独立按键控制流水灯方向和启停/main.c) |
| 06-LED亮灭 | `Keil project/按键/06-独立按键控制LED亮灭/` | K1 翻转单个 LED | [main.c](Keil%20project/按键/06-独立按键控制LED亮灭/main.c) |
| 07-二进制显示 | `Keil project/按键/07-独立按键控制LED显示二进制/` | K1 每按一次二进制 +1 | [main.c](Keil%20project/按键/07-独立按键控制LED显示二进制/main.c) |
| 08-LED移位 | `Keil project/按键/08-独立按键控制LED移位/` | K1 每按一次左移一位 | [main.c](Keil%20project/按键/08-独立按键控制LED移位/main.c) |

### 功能说明（05-方向+启停）

- **K1（P3.1）**：启停流水灯（运行 ↔ 暂停）
- **K2（P3.0）**：切换LED流水方向（D1→D8 ↔ D8→D1）

> 📖 详细笔记：[notes/03_基础外设/按键.md](notes/03_基础外设/按键.md)

## 数码管实验

| 实验 | 路径 | 知识点 | 源码 |
|:---|:---|:---|:---|
| 静态数码管 | `Keil project/数码管/静态数码管显示/` | 段码表、74HC245 + 74HC138 位选 | [main.c](Keil%20project/数码管/静态数码管显示/main.c) |
| 动态数码管 | `Keil project/数码管/动态数码管显示/` | 视觉暂留、位选+段选扫描、消隐 | [main.c](Keil%20project/数码管/动态数码管显示/main.c) |

## 蜂鸣器实验

| 实验 | 路径 | 知识点 | 源码 |
|:---|:---|:---|:---|
| 蜂鸣器 | `Keil project/蜂鸣器/` | 有源/无源区别、ULN2003D 驱动、`BEEP=!BEEP` 定频 | [main.c](Keil%20project/蜂鸣器/main.c) |

## LED点阵实验 ⭐

| 实验 | 路径 | 知识点 | 源码 |
|:---|:---|:---|:---|
| 点阵显示图像 | `Keil project/LED点阵实验/` | 74HC595 串转并、8×8 列扫描、消影、位图取模 | [MAIN.c](Keil%20project/LED点阵实验/MAIN.c) |

> ⚠️ 硬件前提：点阵旁的 **J24 黄色跳线帽**必须短接到 **GND** 一端，否则点阵不亮。
>
> 📖 详细笔记见 Obsidian 库：`04_实验与项目/51单片机学习笔记/03_基础外设/LED点阵.md`

## 笔记系统

学习笔记的**主库在 Obsidian**：`D:\obsidian\qisimiaoxiang\奇思妙想\04_实验与项目\51单片机学习笔记\`

本仓库 [notes/](notes/) 目录保存同步过来的副本：

**00_索引**

- [51单片机MOC.md](notes/00_索引/51单片机MOC.md) — 内容地图与学习路径
- [README.md](notes/00_索引/README.md) — 笔记索引与实验代码速查
- [学习画像.md](notes/00_索引/学习画像.md) — 学习背景与目标

**01_入门准备**

- [开发环境与板子使用指南.md](notes/01_入门准备/开发环境与板子使用指南.md) — Keil / STC-ISP / 板子跳线

**02_编程基础**

- [单片机C编程地基.md](notes/02_编程基础/单片机C编程地基.md) — `typedef`、`#define`、延时函数
- [51单片机C语言实战.md](notes/02_编程基础/51单片机C语言实战.md)

**03_基础外设**

- [GPIO.md](notes/03_基础外设/GPIO.md) — IO 口结构与驱动能力
- [LED.md](notes/03_基础外设/LED.md) — `sbit`、流水灯、移位函数
- [按键.md](notes/03_基础外设/按键.md) — 消抖原理、`key_scan()`、4 个实战工程
- [矩阵按键.md](notes/03_基础外设/矩阵按键.md)
- [蜂鸣器.md](notes/03_基础外设/蜂鸣器.md) — 有源/无源、ULN2003D、《稻香》播放器
- [静态数码管.md](notes/03_基础外设/静态数码管.md) — 段码表、74HC245 + 74HC138
- [动态数码管.md](notes/03_基础外设/动态数码管.md) — 视觉暂留、扫描、消隐、定时器中断重构
- [LED点阵.md](notes/03_基础外设/LED点阵.md) — 74HC595 串转并、8×8 列扫、心形图案

**04_参考资料**

- [模块原理图.md](notes/04_参考资料/模块原理图.md) — 普中A2各模块引脚连接
- [工具库.md](notes/04_参考资料/工具库.md) — `REGX52.H`、`intrins.h`
- [GitHub_LED实验完整手册.md](notes/04_参考资料/GitHub_LED实验完整手册.md)
- [Obsidian_51单片机LED笔记.md](notes/04_参考资料/Obsidian_51单片机LED笔记.md)

> ⚠️ **同步提示**：Obsidian 主库更新更快，`notes/` 下的副本可能滞后。以 Obsidian 为准。

## 下一步

1. 学习**定时器**实现精确延时（替代软件延时）
2. 学习**中断**系统，实现按键中断与定时器中断
3. 把 LED点阵工程改造成自己的版本（换图案 / 加动画）

## 作者

- **freedom** (GitHub: [@FREEdom07289](https://github.com/FREEdom07289))
- 大一电子信息工程专业
