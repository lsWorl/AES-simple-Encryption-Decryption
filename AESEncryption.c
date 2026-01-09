#include "AESEncryption.h"

// AES加密函数
void encrypt(byte key[16], byte input[16], byte output[16]) {
    byte roundKeys[44][4];
    int round;
    
    init_state(input);
    key_expansion(key, roundKeys);
    add_round_key(roundKeys, 0);
    
    for(round = 1; round < Nr; round++) {
        SubBytes();
        shift_rows();
        MixColumns();
        add_round_key(roundKeys, round);
    }
    
    SubBytes();
    shift_rows();
    add_round_key(roundKeys, Nr);
    
    int c, r;
    for(c = 0; c < 4; c++) {
        for(r = 0; r < 4; r++) {
            output[r + 4 * c] = state[r][c];
        }
    }
}
