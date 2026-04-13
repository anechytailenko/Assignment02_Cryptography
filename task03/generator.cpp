#include <iostream>
#include <fstream>
#include <string>

void generateStrumokAutoguess(int rounds, const std::string &filename)
{
    std::ofstream outFile(filename);

    if (!outFile.is_open())
    {
        std::cerr << "Error: file " << filename << " is not opened for writing." << std::endl;
        return;
    }

    outFile << "# Strumok-512 " << rounds << " Rounds\n";
    outFile << "connection relations\n";

    for (int t = 0; t < rounds; ++t)
    {
        // LFSR update
        outFile << "S_" << (t + 16) << ", S_" << (t + 13) << ", S_" << (t + 11) << ", S_" << t << "\n";

        // Gamma update
        outFile << "S_" << (t + 15) << ", R_" << (t + 1) << ", R_" << t << ", S_" << t << "\n";

        // FSM update
        outFile << "R_" << (t + 2) << ", S_" << (t + 13) << ", R_" << t << "\n";
    }

    outFile << "end\n";

    outFile.close();
    std::cout << "File " << filename << " generated successfully (" << rounds << " rounds)." << std::endl;
}

int main()
{
    int numberOfRounds = 11;
    std::string outputFilename = "strumok_11_rounds.txt";

    generateStrumokAutoguess(numberOfRounds, outputFilename);

    return 0;
}