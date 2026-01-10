#ifndef AES_DECRYPTION_H
#define AES_DECRYPTION_H

#include "common.h"

//函数声明
void decrypt(byte key[16], byte input[16], byte output[16]);
void decrypt_file(const char *input_filename, const char *output_filename, byte key[16]);
void decrypt_cbc(byte key[16], byte iv[16], byte *input, byte *output, int length);
#endif // AES_DECRYPTION_H