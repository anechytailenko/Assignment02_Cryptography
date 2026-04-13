#include "Strumok256.h"

void Strumok256::init(const uint64_t K[4], const uint64_t IV[4])
{
    keystreamIndex = 8;

    register1 = 0;
    register2 = 0;

    s[15] = ~K[0];
    s[14] =  K[1];
    s[13] = ~K[2];
    s[12] =  K[3];
    s[11] =  K[0];
    s[10] = ~K[1];
    s[9]  =  K[2];
    s[8]  =  K[3];
    s[7]  = ~K[0];
    s[6]  = ~K[1];
    s[5]  =  K[2] ^ IV[3];
    s[4]  =  K[3];
    s[3]  =  K[0] ^ IV[2];
    s[2]  =  K[1] ^ IV[1];
    s[1]  =  K[2];
    s[0]  =  K[3] ^ IV[0];

    for (int i = 0; i < 32; ++i)
    {
        nextState(true);
    }
    nextState(false);
}