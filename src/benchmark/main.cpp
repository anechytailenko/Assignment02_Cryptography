#include "Strumok256.h"
#include "Strumok512.h"
#include <chrono>
#include <iostream>

constexpr size_t NUMBER_OF_TESTS = 10;

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

void runBenchmark(double (*func)(), const size_t numberOfTests, double *outVector, const std::string &outputMsg)
{
    for (int i = 0; i < numberOfTests; ++i)
    {
        outVector[i] = func();
        std::cout << outputMsg << " Speed: " << outVector[i]<< " MB/s\n";
    }
}

void printAverage(const double *resultsVector, const size_t numberOfTests)
{
    std::cout << std::endl;
    double sum = 0;
    for (int i = 0; i < numberOfTests; ++i)
    {
        sum += resultsVector[i];
    }

    std::cout << "Average: " << (sum / static_cast<double>(numberOfTests)) << " MB/s";
    std::cout << std::endl;
}

int main()
{
    double benchmark256Results[NUMBER_OF_TESTS];
    runBenchmark(benchmark256, NUMBER_OF_TESTS, benchmark256Results, "Strumok-256");
    printAverage(benchmark256Results, NUMBER_OF_TESTS);

    std::cout << std::endl;

    double benchmark512Results[NUMBER_OF_TESTS];
    runBenchmark(benchmark512, NUMBER_OF_TESTS, benchmark512Results, "Strumok-512");
    printAverage(benchmark512Results, NUMBER_OF_TESTS);
    return 0;
}