# 库函数移位 — 流水灯

> 使用 `intrins.h` 的 `_crol_` / `_cror_` 实现双向流水灯

## 知识点

- `_crol_(x, 1)` — 循环左移1位
- `_cror_(x, 1)` — 循环右移1位
- 需要 `#include <intrins.h>`

## 文件

| 文件 | 说明 |
|:---|:---|
| [main-keil头文件.c](main-keil头文件.c) | `_crol_`/`_cror_`版双向流水灯 |
| [STARTUP.A51](STARTUP.A51) | Keil启动文件 |

## 核心代码

```c
#include <intrins.h>

x = _crol_(x, 1);  // 等价于 (x << 1) | (x >> 7)
x = _cror_(x, 1);  // 等价于 (x >> 1) | (x << 7)
```

> 📖 详细笔记：[notes/LED.md](../../../notes/LED.md) §4.3
