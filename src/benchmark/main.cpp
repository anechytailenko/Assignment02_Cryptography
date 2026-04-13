#include "Strumok256.h"
#include "Strumok512.h"
#include <chrono>
#include <iostream>

double benchmark256()
{
    const size_t size_bytes = 1024 * 1024 * 512;
    std::vector<uint8_t> buffer(size_bytes, 0);

    uint64_t key256[32] = {0};
    uint64_t iv[32] = {0};

    Strumok256 cipher256;
    cipher256.init(key256, iv);

    auto start = std::chrono::high_resolution_clock::now();
    cipher256.processBytes(buffer.data(), buffer.data(), size_bytes);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    double speed_mb_s = (size_bytes / (1024.0 * 1024.0)) / elapsed.count();

    return speed_mb_s;
}

double benchmark512()
{
    const size_t size_bytes = 1024 * 1024 * 512;
    std::vector<uint8_t> buffer(size_bytes, 0);

    uint64_t key512[64] = {0};
    uint64_t iv[32] = {0};

    Strumok512 cipher512;
    cipher512.init(key512, iv);

    auto start = std::chrono::high_resolution_clock::now();
    cipher512.processBytes(buffer.data(), buffer.data(), size_bytes);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    double speed_mb_s = (size_bytes / (1024.0 * 1024.0)) / elapsed.count();

    return speed_mb_s;
}


int main()
{
    std::cout << "Strumok-256 Spped: " << benchmark256() << " MB/s\n";
    std::cout << "Strumok-512 Speed: " << benchmark512() << " MB/s\n";
    return 0;
}