#ifndef AES_ENCRYPTION_H
#define AES_ENCRYPTION_H

#include "common.h"

//函数声明
void encrypt(byte key[16], byte input[16], byte output[16]);
void encrypt_cbc(byte key[16], byte iv[16], byte *input, byte *output, int length);
// 文件加密函数
void encrypt_file(const char *input_filename, const char *output_filename, byte key[16]);
#endif // AES_ENCRYPTION_H
