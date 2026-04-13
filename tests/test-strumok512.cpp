#include "StrumokTestFixtures.h"

TEST_F(Strumok512Test, StrumokDstuStandard1)
{
    std::fill(std::begin(key), std::end(key), 0x00);
    key[7] = 0x80;

    std::fill(std::begin(iv), std::end(iv), 0x00);

    uint64_t expected_Z[8] = {
        0xf5b9ab51100f8317ULL,
        0x898ef2086a4af395ULL,
        0x59571fecb5158d0bULL,
        0xb7c45b6744c71fbbULL,
        0xff2efcf05d8d8db9ULL,
        0x7a585871e5c419c0ULL,
        0x6b5c4691b9125e71ULL,
        0xa55be7d2b358ec6eULL
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

TEST_F(Strumok512Test, StrumokDstuStandard2)
{
    std::fill(std::begin(key), std::end(key), 0xaa);
    std::fill(std::begin(iv), std::end(iv), 0x00);

    uint64_t expected_Z[8] = {
        0xd2a6103c50bd4e04ULL,
        0xdc6a21af5eb13b73ULL,
        0xdf4ca6cb07797265ULL,
        0xf453c253d8d01876ULL,
        0x039a64dc7a01800cULL,
        0x688ce327dccb7e84ULL,
        0x41e0250b5e526403ULL,
        0x9936e478aa200f22ULL
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
TEST_F(Strumok512Test, StrumokDstuStandard3)
{
    std::fill(std::begin(key), std::end(key), 0x00);
    key[7] = 0x80;

    std::fill(std::begin(iv), std::end(iv), 0x00);
    iv[0] = 0x04;
    iv[8] = 0x03;
    iv[16] = 0x02;
    iv[24] = 0x01;

    uint64_t expected_Z[8] = {
        0xcca12eae8133aaaaULL,
        0x528d85507ce8501dULL,
        0xda83c7fe3e1823f1ULL,
        0x21416ebf63b71a42ULL,
        0x26d76d2bf1a625ebULL,
        0xeec66ee0cd0b1efcULL,
        0x02dd68f338a345a8ULL,
        0x47538790a5411adbULL
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

TEST_F(Strumok512Test, StrumokDstuStandard4)
{
    std::fill(std::begin(key), std::end(key), 0xaa);

    std::fill(std::begin(iv), std::end(iv), 0x00);
    iv[0] = 0x04;
    iv[8] = 0x03;
    iv[16] = 0x02;
    iv[24] = 0x01;

    uint64_t expected_Z[8] = {
        0x965648e775c717d5ULL,
        0xa63c2a7376e92df3ULL,
        0x0b0eb0bbd47ca267ULL,
        0xea593d979ae5bd39ULL,
        0xd773b5e5193cafe1ULL,
        0xb0a26671d259422bULL,
        0x85b2aa326b280156ULL,
        0x511ace6451435f0cULL
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