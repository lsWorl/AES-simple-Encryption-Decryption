#include "AESDecryption.h"

//使用逆S盒对状态矩阵进行字节替代
void inv_sub_bytes(byte state[4][4])
{
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            state[i][j] = InvSBox[state[i][j]];
        }
    }
}



// 逆行移位操作，即将每一行向右循环移位
void inv_shift_rows(byte state[4][4])
{
    byte temp[4][4];
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            temp[i][j] = state[i][j];
        }
    }
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            state[i][j] = temp[i][(j - i + 4) % 4];
        }
    }
}


// 逆列混合操作
void inv_mix_columns(byte state[4][4])
{
    byte temp[4][4];
    int i, j;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            temp[i][j] = state[i][j];
        }
    }

    for (j = 0; j < 4; j++)
    {
        state[0][j] = (byte)(mul_by_0e(temp[0][j]) ^ mul_by_0b(temp[1][j]) ^ mul_by_0d(temp[2][j]) ^ mul_by_09(temp[3][j]));
        state[1][j] = (byte)(mul_by_09(temp[0][j]) ^ mul_by_0e(temp[1][j]) ^ mul_by_0b(temp[2][j]) ^ mul_by_0d(temp[3][j]));
        state[2][j] = (byte)(mul_by_0d(temp[0][j]) ^ mul_by_09(temp[1][j]) ^ mul_by_0e(temp[2][j]) ^ mul_by_0b(temp[3][j]));
        state[3][j] = (byte)(mul_by_0b(temp[0][j]) ^ mul_by_0d(temp[1][j]) ^ mul_by_09(temp[2][j]) ^ mul_by_0e(temp[3][j]));
    }
}

//解密函数
void decrypt(byte key[16], byte input[16], byte output[16])
{
    byte roundKeys[44][4];
    int round;

    // 使用全局状态矩阵并初始化（common.c 中的 state）
    init_state(input);

    // 密钥扩展
    key_expansion(key, roundKeys);

    // 初始轮密钥加
    add_round_key(roundKeys, Nr);

    // 主轮
    for (round = Nr - 1; round >= 1; round--)
    {
        inv_shift_rows(state);
        inv_sub_bytes(state);
        add_round_key(roundKeys, round);
        inv_mix_columns(state);
    }

    // 最终轮
    inv_shift_rows(state);
    inv_sub_bytes(state);
    add_round_key(roundKeys, 0);

    // 输出结果（从全局 state 读取）
    for (int c = 0; c < 4; c++)
    {
        for (int r = 0; r < 4; r++)
        {
            output[r + 4 * c] = state[r][c];
        }
    }
}

