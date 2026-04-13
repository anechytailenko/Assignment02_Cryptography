#pragma once
#include <cstdint>
#include <cstring>
#include "../include/utils.h"

class StrumokBase
{
protected:
    uint64_t s[16]{};
    uint64_t register1{};
    uint64_t register2{};

    uint8_t keystreamBuffer[8]{};
    size_t keystreamIndex{8};

    void nextState(bool isInit);

public:
    virtual ~StrumokBase();

    uint64_t getKeystreamWord();
    void processBytes(const uint8_t* in, uint8_t* out, size_t length);
};

