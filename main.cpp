#include "pch.h"
#include "ber.h"


using namespace std;

int main(int argc, char * argv[])
{
    bool DEBUG_MODE = false;
    int argNo = 1;

    string path = filesystem::current_path().string();

    char* dataFile1 = 0;
    char* dataFile2 = 0;
    string compData;

    uint64_t diffBits = 0;
    uint64_t compBits = 0;
    uint16_t compTime = 0;

    clock_t startTime;
    clock_t endTime;

    size_t maxSize = 0;
    size_t fileSize1 = 0;
    size_t fileSize2 = 0;

    printf("Bit Error Rate Calculator v1.0\n\n");

    if (argc != 3 && argc != 4) 
    {
        printf("Instruction:\n1.Put two files to .exe directory\n");
        printf("2.Execute file in command line with file's name parameters\n");
        printf("NOTE: You can use debug mode by prefix -d\n\n");
        printf("Have fun!\n\n");
    }

    for (int i = 1; i < argc; i++)
    {
        string p = path + "\\" + argv[i]; //for debugger: path + "\\x64\\Debug\\" + argv[i];

        try
        {
            if (argv[i] == string("-d"))
            {
                printf("Debug mode on.\n");
                DEBUG_MODE = true;
                argNo++; 
            }
            else if (i == argNo)
            {
                //load file
                printf("File 1: %s\n", p.c_str());
                ifstream file1(p.c_str(), ios::binary);
                if (file1.good())
                {
                    //get size of file
                    file1.seekg(0, ios::end);
                    fileSize1 = file1.tellg();
                    file1.seekg(0, ios::beg);
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
                }
            }
            else if (i == argNo+1)
            {
                //load file
                printf("File 2: %s\n", p.c_str());
                ifstream file2(p.c_str(), ios::binary);
                if (file2.good())
                {
                    //get size of file
                    file2.seekg(0, ios::end);
                    fileSize2 = file2.tellg();
                    file2.seekg(0, ios::beg);
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
                }
            }
        }
        catch (const exception ex)
        {
            std::cout << "Error reading file: " << ex.what();
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


    printf("\n___________________________________________");
    printf("\n\nCompared bits: %" PRIu64, compBits);
    printf("\nDifferent bits: %" PRIu64, diffBits);
    printf("\nComputation time[ms]: %" PRIu16, compTime);
    printf("\n___________________________________________\n");

    //printf("\n\nPress ENTER to exit.");
    //cin.get();
    return 0;
}
