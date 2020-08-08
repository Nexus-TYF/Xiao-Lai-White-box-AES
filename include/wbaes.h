#ifndef GENTABLES_H
#define GENTABLES_H

#include "aes.h"
#include "WBMatrix/WBMatrix.h"

u32 TMC[10][8][65536];
M128 M[11];
M128 ex_in, ex_out_inv;

void wbaes_gen(u8 key[16]);
void wbaes_encrypt(u8 input[16], u8 output[16]);
void printstate(unsigned char * in);

#endif // GENTABLES_H