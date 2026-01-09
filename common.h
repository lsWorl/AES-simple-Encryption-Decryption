#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef unsigned char byte; //定义byte类型

#define Nb 4           //列数
#define Nk 4           //密钥长度,以32位字为单位,故当前密钥长度为128位
#define Nr 10          //轮数
#define STATE_SIZE 16  //状态矩阵大小

// 外部变量声明
extern byte state[4][4];  //状态矩阵

// S盒常量声明
extern const byte Sbox[256];

// 轮常量声明
extern const byte Rcon[11];

// 逆S盒常量声明
extern const byte InvSBox[256];

// 函数声明
void init_state(byte input[STATE_SIZE]);
void SubBytes(void);
void shift_rows(void);
byte xtime(byte x);
byte mul_by_03(byte x);
void MixColumns(void);
void rot_word(byte* word);
void sub_word(byte* word);
void key_expansion(byte key[STATE_SIZE], byte roundKeys[44][4]);
void add_round_key(byte roundKeys[44][4], int round);
void print_state(void);
byte mul_by_09(byte x);
byte mul_by_0b(byte x);
byte mul_by_0d(byte x);
byte mul_by_0e(byte x);

#endif // COMMON_H