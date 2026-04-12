#pragma once
#include <gtest/gtest.h>
#include <vector>
#include "Strumok256.h"
#include "Strumok512.h"

inline uint64_t load64LittleEndian(const uint8_t* p) {
    return static_cast<uint64_t>(p[0]) |
          (static_cast<uint64_t>(p[1]) << 8) |
          (static_cast<uint64_t>(p[2]) << 16) |
          (static_cast<uint64_t>(p[3]) << 24) |
          (static_cast<uint64_t>(p[4]) << 32) |
          (static_cast<uint64_t>(p[5]) << 40) |
          (static_cast<uint64_t>(p[6]) << 48) |
          (static_cast<uint64_t>(p[7]) << 56);
}

class Strumok256Test : public ::testing::Test {
protected:
    Strumok256 cipher;
    uint8_t key[32]{};
    uint8_t iv[32]{};
    std::vector<uint8_t> input;
    std::vector<uint8_t> output;
    std::vector<uint8_t> expected;

    void SetUp() override {
        input.assign(64, 0);
        output.assign(64, 0);
        expected.assign(64, 0);
    }

    void initCipher() {
        uint64_t K64[4], IV64[4];
        for (int i = 0; i < 4; ++i) {
            K64[3 - i] = load64LittleEndian(key + i * 8);
            IV64[3 - i] = load64LittleEndian(iv + i * 8);
        }
        cipher.init(K64, IV64);
    }

    void runTestVector(size_t length) {
        initCipher();
        cipher.processBytes(input.data(), output.data(), length);
    }
};

class Strumok512Test : public ::testing::Test {
protected:
    Strumok512 cipher;
    uint8_t key[64]{};
    uint8_t iv[32]{};
    std::vector<uint8_t> input;
    std::vector<uint8_t> output;
    std::vector<uint8_t> expected;

    void SetUp() override {
        input.assign(64, 0);
        output.assign(64, 0);
        expected.assign(64, 0);
    }

    void initCipher() {
        uint64_t K64[8], IV64[4];
        for (int i = 0; i < 8; ++i) {
            K64[7 - i] = load64LittleEndian(key + i * 8);
        }
        for (int i = 0; i < 4; ++i) {
            IV64[3 - i] = load64LittleEndian(iv + i * 8);
        }
        cipher.init(K64, IV64);
    }

    void runTestVector(size_t length) {
        initCipher();
        cipher.processBytes(input.data(), output.data(), length);
    }
};