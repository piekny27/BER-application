#include "pch.h"
#include "ber.h"



int main(int argc, char * argv[])
{
    bool DEBUG_MODE = false;
    int argNo = 1;

    std::string path = std::filesystem::current_path().string();
    std::string logPath = path + "\\log.txt";
    std::fstream logFile(logPath.c_str(), std::ios::out | std::ios::app);

    char* dataFile1 = 0;
    char* dataFile2 = 0;
    std::string compData;

    uint64_t diffBits = 0;
    uint64_t compBits = 0;
    uint16_t compTime = 0;
    float berValue = 0;

    clock_t startTime;
    clock_t endTime;

    size_t maxSize = 0;
    size_t fileSize1 = 0;
    size_t fileSize2 = 0;

    printf("\nBit Error Rate Calculator v1.0\n\n");  
    logFilePrint(logFile, " Start Bit Error Rate Calculator v1.0\n");

    if (argc != 3 && argc != 4) 
    {
        printf("Instruction:\n1.Put two files to .exe directory\n");
        printf("2.Execute file in command line with file's name parameters\n");
        printf("NOTE: You can use debug mode by prefix -d\n\n");
        printf("Have fun!\n\n");
    }

    for (int i = 1; i < argc; i++)
    {
        std::string p = path + "\\x64\\Debug\\" + argv[i]; //for debugger: path + "\\x64\\Debug\\" + argv[i];

        try
        {
            if (argv[i] == std::string("-d"))
            {
                printf("Debug mode on.\n");
                logFilePrint(logFile, " Debug mode on.\n");
                DEBUG_MODE = true;
                argNo++; 
            }
            else if (i == argNo)
            {
                //load file
                printf("File 1: %s\n", p.c_str());
                logFilePrint(logFile, " Loading File 1: " + std::string(p) + "\n");
                std::ifstream file1(p.c_str(), std::ios::binary);
                if (file1.good())
                {
                    //get size of file
                    file1.seekg(0, std::ios::end);
                    fileSize1 = file1.tellg();
                    file1.seekg(0, std::ios::beg);
                    if (maxSize < fileSize1) maxSize = fileSize1;
                    //create array and save bytes
                    dataFile1 = new char[fileSize1 + 1];
                    file1.read(dataFile1, fileSize1);
                    //add null for pointer
                    dataFile1[fileSize1] = '\0';
                }
                else
                {
                    printf("File not found.\n");
                    logFilePrint(logFile, " File 1 not found.\n");
                }
            }
            else if (i == argNo+1)
            {
                //load file
                printf("File 2: %s\n", p.c_str());
                logFilePrint(logFile, "Loading File 2: " + std::string(p) + "\n");
                std::ifstream file2(p.c_str(), std::ios::binary);
                if (file2.good())
                {
                    //get size of file
                    file2.seekg(0, std::ios::end);
                    fileSize2 = file2.tellg();
                    file2.seekg(0, std::ios::beg);
                    if (maxSize < fileSize2) maxSize = fileSize2;
                    //create array and save bytes
                    dataFile2 = new char[fileSize2 + 1];
                    file2.read(dataFile2, fileSize2);
                    //add null for pointer
                    dataFile2[fileSize2] = '\0';
                }
                else
                {
                    printf("File not found.\n");
                    logFilePrint(logFile, " File 2 not found.\n");
                }
            }
        }
        catch (const std::exception ex)
        {
            printf("Error reading file: %s", ex.what());
            logFilePrint(logFile, " Error reading file " + std::string(ex.what()) + "\n");
            return 0;
        }
    }

    //compare two files with hamming distance alghoritm
    startTime = clock();
    for (int i = 0; i < maxSize; i++)
    {
        if (i < fileSize1 && i < fileSize2)
        {
            hammingDistance(dataFile1[i], dataFile2[i], diffBits, compBits);
            if (DEBUG_MODE)
            {
                printf("\n%d| ", i);
                toBinaryPrint(dataFile1[i]);
                toBinaryPrint(dataFile2[i]);
                printf(" |diff: %" PRIu64, diffBits);
                printf(" |comp: %" PRIu64, compBits);
            }
        }
        else if (i >= fileSize2 && i < fileSize1)
        {
            hammingDistance(dataFile1[i], 0, diffBits, compBits);
            if (DEBUG_MODE)
            {
                printf("\n%d| ", i);
                toBinaryPrint(dataFile1[i]);
                toBinaryPrint(0);
                printf(" |diff: %" PRIu64, diffBits);
                printf(" |comp: %" PRIu64, compBits);
            }
        }
        else if (i >= fileSize1 && i < fileSize2)
        {
            hammingDistance(0, dataFile2[i], diffBits, compBits);
            if (DEBUG_MODE)
            {
                printf("\n%d| ", i);
                toBinaryPrint(0);
                toBinaryPrint(dataFile2[i]);
                printf(" |diff: %" PRIu64, diffBits);
                printf(" |comp: %" PRIu64, compBits);
            }
        }
    }
    endTime = clock();
    compTime = (endTime - startTime);
    berValue = ((float)diffBits / (float)compBits) * 100.0;

    printf("\n___________________________________________");
    printf("\n\nCompared bits: %" PRIu64, compBits);
    printf("\nDifferent bits: %" PRIu64, diffBits);
    printf("\nComputation time[ms]: %" PRIu16, compTime);
    printf("\nBit Error Rate: %f%%" , berValue);
    printf("\n___________________________________________\n");

    logFilePrint(logFile, 
        " Calculation done: Compared bits: " + std::to_string(compBits) +
        ", Different bits: " + std::to_string(diffBits) +
        ", Computation time[ms]: " + std::to_string(compTime) +
        ", Bit Error Rate: " + std::to_string(berValue) + "\n");

    logFilePrint(logFile, " Close Bit Error Rate Calculator v1.0\n");
    logFile.close();

    printf("\n\nPress ENTER to exit.");
    std::cin.get();
    return 0;
}
