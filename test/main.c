#include "wbaes.h"

int main(int argc, char * argv[])
{
    unsigned char IN[16] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};
    unsigned char EX_IN[16];
    unsigned char EX_OUT[16];
    unsigned char OUT[16];
    unsigned char OOUT[16];
    u8 key[16] = {0};
    V128 state_M;
    u8 *temp_u8;

    wbaes_gen(key); 
    // external encodings
    for(int i = 0; i < 8; i++)
    {
        temp_u8 = (u8 *)&state_M.V[0];
        *(temp_u8 + (7 - i)) = IN[i];
    }
    for(int i = 8; i < 16; i++)
    {
        temp_u8 = (u8 *)&state_M.V[1];
        *(temp_u8 + (15 - i)) = IN[i];
    }
    MatMulVecM128(ex_in, state_M, &state_M);
    for(int i = 0; i < 8; i++)
    {
        temp_u8 = (u8 *)&state_M.V[0];
        EX_IN[i] = *(temp_u8 + (7 - i));
    }
    for(int i = 8; i < 16; i++)
    {
        temp_u8 = (u8 *)&state_M.V[1];
        EX_IN[i] = *(temp_u8 + (15 - i));
    }
    // encryption
    wbaes_encrypt(EX_IN, EX_OUT);
    // external encodings
    for(int i = 0; i < 8; i++)
    {
        temp_u8 = (u8 *)&state_M.V[0];
        *(temp_u8 + (7 - i)) = EX_OUT[i];
    }
    for(int i = 8; i < 16; i++)
    {
        temp_u8 = (u8 *)&state_M.V[1];
        *(temp_u8 + (15 - i)) = EX_OUT[i];
    }
    MatMulVecM128(ex_out_inv, state_M, &state_M);
    for(int i = 0; i < 8; i++)
    {
        temp_u8 = (u8 *)&state_M.V[0];
        OUT[i] = *(temp_u8 + (7 - i));
    }
    for(int i = 8; i < 16; i++)
    {
        temp_u8 = (u8 *)&state_M.V[1];
        OUT[i] = *(temp_u8 + (15 - i));
    }
    printstate(OUT);
    
    aes_128_encrypt(IN, key, OOUT);
    printstate(OOUT);
    return 0;
}
