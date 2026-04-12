#include "StrumokTestFixtures.h"

TEST_F(Strumok256Test, StrumokDstuStandard1)
{
    std::fill(std::begin(key), std::end(key), 0x00);
    key[7] = 0x80;

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

TEST_F(Strumok256Test, StrumokDstuStandard2)
{
    std::fill(std::begin(key), std::end(key), 0xaa);
    std::fill(std::begin(iv), std::end(iv), 0x00);

    uint64_t expected_Z[8] = {
        0xa7510b38c7a95d1dULL,
        0xcd5ea28a15b8654fULL,
        0xc5e2e2771d0373b2ULL,
        0x98ae829686d5fceeULL,
        0x45bddf65c523dbb8ULL,
        0x32a93fcdd950001fULL,
        0x752a7fb588af8c51ULL,
        0x9de92736664212d4ULL
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

TEST_F(Strumok256Test, StrumokDstuStandard3)
{
    std::fill(std::begin(key), std::end(key), 0x00);
    key[7] = 0x80;

    std::fill(std::begin(iv), std::end(iv), 0x00);
    iv[0] = 0x04;
    iv[8] = 0x03;
    iv[16] = 0x02;
    iv[24] = 0x01;

    uint64_t expected_Z[8] = {
        0xfe44a2508b5a2acdULL,
        0xaf355b4ed21d2742ULL,
        0xdcd7fdd6a57a9e71ULL,
        0x5d267bd2739fb5ebULL,
        0xb22eee96b2832072ULL,
        0xc7de6a4cdaa9a847ULL,
        0x72d5da93812680f2ULL,
        0x4a0acb7e93da2ce0ULL
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

TEST_F(Strumok256Test, StrumokDstuStandard4)
{
    std::fill(std::begin(key), std::end(key), 0xaa);

    std::fill(std::begin(iv), std::end(iv), 0x00);
    iv[0] = 0x04;
    iv[8] = 0x03;
    iv[16] = 0x02;
    iv[24] = 0x01;

    uint64_t expected_Z[8] = {
        0xe6d0efd9cea5abcdULL,
        0x1e78ba1a9b0e401eULL,
        0xbcfbea2c02ba0781ULL,
        0x1bd375588ae08794ULL,
        0x5493cf21e114c209ULL,
        0x66cd5d7cc7d0e69aULL,
        0xa5cdb9f3380d07faULL,
        0x2940d61a4d4e9ce4ULL
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