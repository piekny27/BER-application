#include "ber.h"

time_t result = std::time(nullptr);
std::ofstream newFile;

void hammingDistance(uint8_t n1, uint8_t n2, uint64_t& diffBits, uint64_t& compBits)
{
    uint8_t x = n1 ^ n2;
    uint8_t setBits = 0;

    while (x > 0)
    {
        setBits += x & 1;
        x >>= 1;
    }
    diffBits += setBits;
    compBits += 8;
}

void toBinaryPrint(uint8_t a)
{
    uint8_t j;
    for (j = 0x80; j != 0; j >>= 1)
    {
        printf("%c", (a & j) ? '1' : '0');
    }       
    printf(" ");
}

void logFilePrint(std::fstream& logFile, std::string message)
{
    result = std::time(nullptr);
    logFile << strtok(asctime(localtime(&result)), "\n") << message;
}

bool createFile(std::string path, std::string fileName, size_t fileSize, uint8_t value)
{
    std::fstream newFile(path+fileName, std::ios::out | std::ios::binary);
    char* _str = new char[fileSize + 1];

    for (uint64_t i = 0; i < fileSize; i++)
    {
        _str[i] = value;
    }
    _str[fileSize] = '\0';

    if (newFile.is_open())
    {
        newFile.write(_str, fileSize);
        newFile.close();
        return true;
    }
    else
    {
        printf("The file is not open.\n");
        return false;
    }
}