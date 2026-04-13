#include "Strumok256.h"
#include "Strumok512.h"
#include <iostream>
#include <iomanip>

enum class Version
{
    Strumok256,
    Strumok512
};

void strumok256Usage(const std::string &plaintext)
{
    uint8_t key[32] = {0x11, 0x09, 0x20, 0x01};
    uint8_t iv[32]  = {0x01, 0x04, 0x08, 0x07};

    uint64_t K64[4], IV64[4];
    for (int i = 0; i < 4; ++i) {
        K64[3 - i] = load64LittleEndian(key + i * 8);
        IV64[3 - i] = load64LittleEndian(iv + i * 8);
    }

    std::vector<uint8_t> plaintextBytes(plaintext.begin(), plaintext.end());
    std::vector<uint8_t> ciphertext(plaintextBytes.size());
    std::vector<uint8_t> decryptedBytes(plaintextBytes.size());

    Strumok256 cipher;

    cipher.init(K64, IV64);
    cipher.processBytes(plaintextBytes.data(), ciphertext.data(), plaintextBytes.size());

    cipher.init(K64, IV64);
    cipher.processBytes(ciphertext.data(), decryptedBytes.data(), ciphertext.size());

    std::string decryptedText(decryptedBytes.begin(), decryptedBytes.end());

    std::cout << "Plaintext:  " << plaintext << std::endl;
    std::cout << "Ciphertext: ";
    for (uint8_t b : ciphertext) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << std::to_string(b);
    }
    std::cout << std::endl;
    std::cout << "Decrypted:  " << decryptedText << std::endl;
}


void strumok512Usage(const std::string &plaintext)
{
    uint8_t key[64] = {0x67, 0xFF, 0xAB, 0xCD, 0x14, 0x88, 0xBB, 0x0A};
    uint8_t iv[32]  = {0x11, 0x45, 0x12, 0x32};

    uint64_t K64[8], IV64[4];

    for (int i = 0; i < 8; ++i) {
        K64[7 - i] = load64LittleEndian(key + i * 8);
    }

    for (int i = 0; i < 4; ++i) {
        IV64[3 - i] = load64LittleEndian(iv + i * 8);
    }

    std::vector<uint8_t> plaintextBytes(plaintext.begin(), plaintext.end());
    std::vector<uint8_t> ciphertext(plaintextBytes.size());
    std::vector<uint8_t> decryptedBytes(plaintextBytes.size());

    Strumok512 cipher;

    cipher.init(K64, IV64);
    cipher.processBytes(plaintextBytes.data(), ciphertext.data(), plaintextBytes.size());

    cipher.init(K64, IV64);
    cipher.processBytes(ciphertext.data(), decryptedBytes.data(), ciphertext.size());

    std::string decryptedText(decryptedBytes.begin(), decryptedBytes.end());

    std::cout << "Plaintext:  " << plaintext << std::endl;
    std::cout << "Ciphertext: ";
    for (uint8_t b : ciphertext) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << std::to_string(b);
    }
    std::cout << std::endl;
    std::cout << "Decrypted:  " << decryptedText << std::endl;
}

void consecutivePrint(size_t size, char charToPrint)
{
    for (int i = 0; i < size; ++i)
    {
        std::cout << charToPrint;
    }
}

void printTitle(const std::string &title)
{
    consecutivePrint(38 + title.size(), '=');
    std::cout << std::endl;

    consecutivePrint(16, '=');
    consecutivePrint(3, ' ');
    std::cout << title;
    consecutivePrint(3, ' ');
    consecutivePrint(16, '=');
    std::cout << std::endl;
}


void displayAll(Version version, const std::string &title, const std::string &plaintext)
{
    printTitle(title);
    std::cout << std::endl;

    switch (version)
    {
    case Version::Strumok256:
        strumok256Usage(plaintext);
        break;

    case Version::Strumok512:
        strumok512Usage(plaintext);
        break;
    }

    std::cout << std::endl;
    consecutivePrint(38 + title.size(), '=');
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
}


int main()
{
    // displayAll(Version::Strumok256, "Strumok 256 Usage", "Those who want to live, let them fight, and those who do not want to fight in this world of eternal struggle do not deserve...");
    displayAll(Version::Strumok256, "Strumok 256 Usage", "Hi, you asked about cryptocurrency to buy: here is my advice according to...");
    displayAll(Version::Strumok512, "Strumok 512 Usage", "I invite you to my party at Little Saint James");

    return 0;
}