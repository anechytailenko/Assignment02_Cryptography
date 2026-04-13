#include <gtest/gtest.h>
#include <iostream>
#include <iomanip>
#include "Strumok512.h"
#include "../include/utils.h"
using namespace std;

uint64_t mock_invT(uint64_t r2_val, const uint64_t true_R1[13], const uint64_t true_R2[13])
{
    for (int i = 1; i < 13; i++)
    {
        if (true_R2[i] == r2_val)
            return true_R1[i - 1];
    }
    return 0;
}

class StrumokAttacker : public Strumok512
{
public:
    void extractTruth(uint64_t true_S[27], uint64_t true_R1[13], uint64_t true_R2[13], uint64_t Z[11])
    {
        for (int i = 0; i < 16; i++)
        {
            true_S[i] = s[i];
        }
        true_R1[0] = register1;
        true_R2[0] = register2;

        for (int t = 0; t < 11; t++)
        {
            Z[t] = getKeystreamWord();
            true_S[t + 16] = s[15];
            true_R1[t + 1] = register1;
            true_R2[t + 1] = register2;
        }
    }
};

TEST(StrumokAttackTest, SimulateGuessAndDetermine)
{
    cout << "\n=== RUN ATTACK SIMYLATION USING GUESS-AND-DETERMINE technique ===" << endl;

    StrumokAttacker cipher;
    uint64_t K[8] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
    uint64_t IV[4] = {0xAA, 0xBB, 0xCC, 0xDD};
    cipher.init(K, IV);

    uint64_t true_S[27] = {0};
    uint64_t true_R1[13] = {0};
    uint64_t true_R2[13] = {0};
    uint64_t Z[11] = {0};

    cipher.extractTruth(true_S, true_R1, true_R2, Z);

    // Massive that hacker will use to store derived variables during the attack
    uint64_t S[27] = {0};
    uint64_t R1[13] = {0};
    uint64_t R2[13] = {0};

    // Basis variables (7 variables) that Autoguess determine for us(note amount of variables is 9 because we use unified R optimisation when run Autoguess) )
    S[16] = true_S[16];
    R1[0] = true_R1[0];
    R2[1] = true_R2[1];
    S[3] = true_S[3];
    R1[4] = true_R1[4];
    R2[5] = true_R2[5];
    S[20] = true_S[20];
    S[21] = true_S[21];
    S[5] = true_S[5];

    cout << "-> Attacker is simulating the attack having gamma and the correct guessed basis variables." << endl;
    cout << "-> Run determination..." << endl;

    // State 0
    R2[3] = R1[4] - S[16];
    R1[2] = mock_invT(R2[3], true_R1, true_R2); // Проход через обратный S-box!
    S[18] = S[21] ^ strumok_AlphaMul(S[5]) ^ strumok_AlphaInvMul(S[16]);
    R1[5] = ((Z[5] ^ S[5]) ^ R2[5]) - S[20];
    R2[6] = strumok_T(R1[5]); // Прямой S-box

    // State 1
    S[14] = R1[2] - R2[1];
    R1[3] = ((Z[3] ^ S[3]) ^ R2[3]) - S[18];
    R2[4] = strumok_T(R1[3]);
    R1[6] = R2[5] + S[18];
    R2[7] = strumok_T(R1[6]);

    // State 2
    S[19] = strumok_AlphaMul(S[3]) ^ strumok_AlphaInvMul(S[14]) ^ S[16];
    S[17] = R1[5] - R2[4];
    S[6] = Z[6] ^ ((S[21] + R1[6]) ^ R2[6]);
    R1[8] = R2[7] + S[20];
    R2[9] = strumok_T(R1[8]);

    // State 3
    S[4] = Z[4] ^ ((S[19] + R1[4]) ^ R2[4]);
    S[22] = strumok_AlphaMul(S[6]) ^ strumok_AlphaInvMul(S[17]) ^ S[19];
    R1[7] = R2[6] + S[19];
    R2[8] = strumok_T(R1[7]);

    // State 4
    S[15] = strumok_AlphaMul(S[20] ^ strumok_AlphaMul(S[4]) ^ S[17]);
    S[7] = Z[7] ^ ((S[22] + R1[7]) ^ R2[7]);
    R1[9] = R2[8] + S[21];
    R2[10] = strumok_T(R1[9]);
    R1[10] = R2[9] + S[22];
    R2[11] = strumok_T(R1[10]);

    // State 5
    R2[2] = R1[3] - S[15];
    R1[1] = mock_invT(R2[2], true_R1, true_R2);
    S[23] = strumok_AlphaMul(S[7]) ^ strumok_AlphaInvMul(S[18]) ^ S[20];

    // State 6
    S[1] = Z[1] ^ ((S[16] + R1[1]) ^ R2[1]);
    S[2] = Z[2] ^ ((S[17] + R1[2]) ^ R2[2]);
    S[8] = Z[8] ^ ((S[23] + R1[8]) ^ R2[8]);
    R1[11] = R2[10] + S[23];
    R2[12] = strumok_T(R1[11]);

    // State 7
    S[12] = strumok_AlphaMul(S[17] ^ strumok_AlphaMul(S[1]) ^ S[14]);
    S[13] = strumok_AlphaMul(S[18] ^ strumok_AlphaMul(S[2]) ^ S[15]);
    S[24] = strumok_AlphaMul(S[8]) ^ strumok_AlphaInvMul(S[19]) ^ S[21];

    // State 8
    R2[0] = R1[1] - S[13];
    S[9] = Z[9] ^ ((S[24] + R1[9]) ^ R2[9]);

    // State 9
    S[0] = Z[0] ^ ((S[15] + R1[0]) ^ R2[0]);
    S[25] = strumok_AlphaMul(S[9]) ^ strumok_AlphaInvMul(S[20]) ^ S[22];

    // State 10
    S[11] = strumok_AlphaMul(S[16] ^ strumok_AlphaMul(S[0]) ^ S[13]);
    S[10] = Z[10] ^ ((S[25] + R1[10]) ^ R2[10]);

    // State 11
    S[26] = strumok_AlphaMul(S[10]) ^ strumok_AlphaInvMul(S[21]) ^ S[23];

    cout << "=== RESULTS ===" << endl;
    cout << "CHECK 40 determined variables " << endl;

    bool success = true;
    for (int i = 0; i < 27; i++)
    {
        if (S[i] != true_S[i])
            success = false;
        EXPECT_EQ(S[i], true_S[i]) << "Mismatch at S[" << i << "]";
    }

    for (int i = 0; i < 12; i++)
    {
        if (R1[i] != true_R1[i] || R2[i] != true_R2[i])
            success = false;
        EXPECT_EQ(R1[i], true_R1[i]) << "Mismatch at R1[" << i << "]";
        EXPECT_EQ(R2[i], true_R2[i]) << "Mismatch at R2[" << i << "]";
    }

    if (success)
    {
        cout << "[SUCCESS] Internal state fully matches the original" << endl;
    }
    else
    {
        cout << "[ERROR] Internal state does NOT match the original" << endl;
    }
    cout << "======================================================\n";
}