#ifndef AES_ENCRYPTION_H
#define AES_ENCRYPTION_H

#include "common.h"

// AES加密函数
void encrypt(byte key[16], byte input[16], byte output[16]);

#endif // AES_ENCRYPTION_H
