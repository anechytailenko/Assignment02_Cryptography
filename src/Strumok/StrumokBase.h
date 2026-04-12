#pragma once
#include <cstdint>
#include "../include/utils.h"

class StrumokBase
{
protected:
    uint64_t s[16]{};
    uint64_t register1{};
    uint64_t register2{};

    void nextState(bool isInit);

public:
    uint64_t getKeystreamWord();
};

