#pragma once
#include "StrumokBase.h"

class Strumok512 : public StrumokBase
{
public:
    void init(const uint64_t K[8], const uint64_t IV[4]);
};
