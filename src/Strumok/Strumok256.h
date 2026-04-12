#pragma once
#include "StrumokBase.h"

class Strumok256 : public StrumokBase
{
public:
    void init(const uint64_t K[4], const uint64_t IV[4]);
};
