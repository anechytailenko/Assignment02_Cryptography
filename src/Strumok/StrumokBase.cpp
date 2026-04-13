#include "StrumokBase.h"

StrumokBase::~StrumokBase()
{
    std::memset(s, 0, sizeof(s));
    std::memset(&register1, 0, sizeof(register1));
    std::memset(&register2, 0, sizeof(register2));
    std::memset(keystreamBuffer, 0, sizeof(keystreamBuffer));
}

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

void StrumokBase::processBytes(const uint8_t* in, uint8_t* out, size_t length)
{
    while (length > 0 && keystreamIndex < 8)
    {
        *out++ = *in++ ^ keystreamBuffer[keystreamIndex++];
        length--;
    }

    while (length >= 8)
    {
        uint64_t word = getKeystreamWord();
        uint64_t inBlock;
        
        std::memcpy(&inBlock, in, 8);
        uint64_t outBlock = inBlock ^ word;
        std::memcpy(out, &outBlock, 8);
        
        in += 8;
        out += 8;
        length -= 8;
    }

    if (length > 0)
    {
        uint64_t word = getKeystreamWord();
        keystreamBuffer[0] = static_cast<uint8_t>(word);
        keystreamBuffer[1] = static_cast<uint8_t>(word >> 8);
        keystreamBuffer[2] = static_cast<uint8_t>(word >> 16);
        keystreamBuffer[3] = static_cast<uint8_t>(word >> 24);
        keystreamBuffer[4] = static_cast<uint8_t>(word >> 32);
        keystreamBuffer[5] = static_cast<uint8_t>(word >> 40);
        keystreamBuffer[6] = static_cast<uint8_t>(word >> 48);
        keystreamBuffer[7] = static_cast<uint8_t>(word >> 56);
        keystreamIndex = 0;

        while (length > 0)
        {
            *out++ = *in++ ^ keystreamBuffer[keystreamIndex++];
            length--;
        }
    }
}