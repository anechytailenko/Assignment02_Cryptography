#include "StrumokBase.h"

void StrumokBase::nextState(bool isInit)
{
    uint64_t outWord = (s[15] + register1) ^ register2;

    uint64_t register2Next = strumok_T(register1);
    uint64_t register1Next = register2 + s[13];

    uint64_t sa15Next = strumok_AlphaMul(s[0]) ^ strumok_AlphaInvMul(s[11]) ^ s[13];
    if (isInit) {
        sa15Next ^= outWord;
    }

    register2 = register2Next;
    register1 = register1Next;

    for (int i = 0; i < 15; ++i) {
        s[i] = s[i + 1];
    }
    s[15] = sa15Next;
}

uint64_t StrumokBase::getKeystreamWord(){
    uint64_t word = ((s[15] + register1) ^ register2) ^ s[0];
    nextState(false);
    return word;
}
