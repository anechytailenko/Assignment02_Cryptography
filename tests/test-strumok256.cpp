#include "StrumokTestFixtures.h"

TEST_F(Strumok256Test, StrumokDstuStandard1)
{
    std::fill(std::begin(key), std::end(key), 0x00);
    key[31] = 0x80;

    std::fill(std::begin(iv), std::end(iv), 0x00);

    uint64_t expected_Z[8] = {
        0xe442d15345dc66caULL,
        0xf47d700ecc66408aULL,
        0xb4cb284b5477e641ULL,
        0xa2afc9092e4124b0ULL,
        0x728e5fa26b11a7d9ULL,
        0xe6a7b9288c68f972ULL,
        0x70eb3606de8ba44cULL,
        0xaced7956bd3e3de7ULL
    };

    for (int i = 0; i < 8; ++i) {
        expected[i * 8 + 0] = static_cast<uint8_t>(expected_Z[i]);
        expected[i * 8 + 1] = static_cast<uint8_t>(expected_Z[i] >> 8);
        expected[i * 8 + 2] = static_cast<uint8_t>(expected_Z[i] >> 16);
        expected[i * 8 + 3] = static_cast<uint8_t>(expected_Z[i] >> 24);
        expected[i * 8 + 4] = static_cast<uint8_t>(expected_Z[i] >> 32);
        expected[i * 8 + 5] = static_cast<uint8_t>(expected_Z[i] >> 40);
        expected[i * 8 + 6] = static_cast<uint8_t>(expected_Z[i] >> 48);
        expected[i * 8 + 7] = static_cast<uint8_t>(expected_Z[i] >> 56);
    }

    runTestVector(64);

    for (size_t i = 0; i < 64; ++i) {
        EXPECT_EQ(output[i], expected[i]) << "Mismatch at byte index " << i;
    }
}