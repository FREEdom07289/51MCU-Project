/**
 * @file    main.c
 * @brief   矩阵键盘密码锁：4 位密码输入、LCD1602 显示、正确/错误提示
 * @author  FREEDOM
 * @version V1.0
 * @date    2026-11-22
 * @note    硬件：STC89C52RC + 4×4 矩阵键盘（P1）+ LCD1602（P0 数据，P2.5~P2.7 控制）
 *          按键：S1~S9 → 1~9，S10 → 0，S11 → 删除一位，S12 → 确认，S13~S16 保留
 *          密码：4 位，默认 1234（改 PASSWORD 数组即可）
 *          现象：第 1 行固定显示 PASSWORD LOCK；第 2 行用 * 表示已输入位数、_ 表示空位；
 *                输满 4 位按 S12：正确显示 OPEN，错误显示 ERROR，2 秒后回到输入界面
 *          依赖模块：LCD1602.c、MatrixKey_Scan.c、Delay.c
 *          修改记录：
 *            V1.0 2026-11-22 首版：4 位密码 + 确认/删除 + LCD 提示
 */
#include <REGX52.H>
#include "LCD1602.h"
#include "MatrixKey_Scan.h"
#include "Delay.h"

/* ==================== 私有宏 ==================== */

#define PASSWORD_LENGTH     4       /* 密码位数 */
#define MESSAGE_MS          2000    /* OPEN / ERROR 停留时间，单位 ms */
#define PROMPT_MS           800     /* “位数不够”提示停留时间，单位 ms */
#define KEY_ENTER           12      /* S12：确认 */
#define KEY_BACKSPACE       11      /* S11：删除一位 */
#define KEY_ZERO            10      /* S10：数字 0 */

/* ==================== 全局变量 ==================== */

/* code：放进 Flash，不占 RAM。密码 1-2-3-4，按需改成自己的四位 */
unsigned char code PASSWORD[PASSWORD_LENGTH] = {1, 2, 3, 4};

static unsigned char LastKey  = 0;                      /* 上一轮扫到的键号，用于“按一次只算一次” */
static unsigned char InputCnt = 0;                      /* 已输入位数，0 ~ PASSWORD_LENGTH */
static unsigned char InputBuf[PASSWORD_LENGTH];         /* 已输入的密码数字，0 ~ 9 */

/* ==================== 私有函数声明 ==================== */

static void Lock_Refresh(void);
static void Lock_AddDigit(unsigned char Digit);
static void Lock_Backspace(void);
static void Lock_Confirm(void);
static void Lock_ShowMessage(char *Message);
static unsigned char Lock_CheckPassword(void);

/* ==================== 主函数 ==================== */

void main(void)
{
    unsigned char Key;

    LCD1602_Init();
    LCD1602_ShowString(1, 1, "PASSWORD LOCK");
    Lock_Refresh();

    while (1)
    {
        Key = MatrixKey_Scan();

        if (Key == LastKey)             /* 按住不放：同一个键只处理一次 */
        {
            continue;
        }
        LastKey = Key;                  /* 记住本轮键号；松手时它变成 0 */

        if (Key == 0)                   /* 松手，没有动作 */
        {
            continue;
        }

        if ((Key >= 1) && (Key <= 9))   /* S1~S9 → 数字 1~9 */
        {
            Lock_AddDigit(Key);
        }
        else if (Key == KEY_ZERO)       /* S10 → 数字 0 */
        {
            Lock_AddDigit(0);
        }
        else if (Key == KEY_BACKSPACE)  /* S11 → 退一格 */
        {
            Lock_Backspace();
        }
        else if (Key == KEY_ENTER)      /* S12 → 校验 */
        {
            Lock_Confirm();
        }
        /* S13~S16：保留给后续功能（改密码、上锁等） */
    }
}

/* ==================== 私有函数实现 ==================== */

/**
 * @brief  刷新第 2 行输入界面
 * @retval None
 * @note   已输入的位显示 *，未输入的位显示 _，例如已输 2 位显示 Code: * * _ _
 */
static void Lock_Refresh(void)
{
    char Line[17];
    unsigned char i;

    for (i = 0; i < 16; i++)
    {
        Line[i] = ' ';
    }
    Line[16] = '\0';

    Line[0] = 'C';
    Line[1] = 'o';
    Line[2] = 'd';
    Line[3] = 'e';
    Line[4] = ':';

    for (i = 0; i < PASSWORD_LENGTH; i++)     /* 4 个槽位放在第 7、9、11、13 列 */
    {
        Line[6 + i * 2] = (i < InputCnt) ? '*' : '_';
    }

    LCD1602_ShowString(2, 1, Line);
}

/**
 * @brief  追加一位密码
 * @param  Digit 0 ~ 9
 * @retval None
 * @note   已满 4 位时忽略；不在驱动里判满，调用者决定规则
 */
static void Lock_AddDigit(unsigned char Digit)
{
    if (InputCnt >= PASSWORD_LENGTH)
    {
        return;
    }

    InputBuf[InputCnt] = Digit;
    InputCnt++;
    Lock_Refresh();
}

/**
 * @brief  删除最后一位
 * @retval None
 */
static void Lock_Backspace(void)
{
    if (InputCnt == 0)
    {
        return;
    }

    InputCnt--;
    Lock_Refresh();
}

/**
 * @brief  校验密码并给出结果
 * @retval None
 * @note   位数不足时提示“4 DIGITS”后返回，不校验；结果停留后自动清空回到输入
 */
static void Lock_Confirm(void)
{
    if (InputCnt != PASSWORD_LENGTH)
    {
        Lock_ShowMessage("4 DIGITS");
        Delay_ms(PROMPT_MS);
        Lock_Refresh();
        return;
    }

    if (Lock_CheckPassword())
    {
        Lock_ShowMessage("OPEN");           /* 实际项目可在此驱动继电器/舵机开锁 */
    }
    else
    {
        Lock_ShowMessage("ERROR");          /* 实际项目可在此计数错误次数、蜂鸣器报警 */
    }

    Delay_ms(MESSAGE_MS);
    InputCnt = 0;                           /* 无论对错，回到初始输入状态 */
    Lock_Refresh();
}

/**
 * @brief  在第 2 行居中显示一条提示
 * @param  Message 提示字符串，长度不超过 16
 * @retval None
 */
static void Lock_ShowMessage(char *Message)
{
    char Line[17];
    unsigned char Len = 0;
    unsigned char Start;
    unsigned char i;

    while ((Message[Len] != '\0') && (Len < 16))
    {
        Len++;
    }
    Start = (unsigned char)((16 - Len) / 2);

    for (i = 0; i < 16; i++)
    {
        Line[i] = ' ';
    }
    Line[16] = '\0';

    for (i = 0; i < Len; i++)
    {
        Line[Start + i] = Message[i];
    }

    LCD1602_ShowString(2, 1, Line);
}

/**
 * @brief  逐位比对输入的密码与预设密码
 * @retval 1 = 正确，0 = 错误
 */
static unsigned char Lock_CheckPassword(void)
{
    unsigned char i;

    for (i = 0; i < PASSWORD_LENGTH; i++)
    {
        if (InputBuf[i] != PASSWORD[i])
        {
            return 0;
        }
    }
    return 1;
}