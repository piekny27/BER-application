#include "pch.h"
#include "ber.h"


using namespace std;

int main(int argc, char * argv[])
{
    string path = filesystem::current_path().string();

    char* dataFile1 = 0;
    char* dataFile2 = 0;
    char* compData = 0;

    size_t maxSize = 0;
    size_t fileSize1 = 0;
    size_t fileSize2 = 0;

    printf("Bit Error Rate Calculator v1.0\n");

    for (int i = 1; i < argc; i++) 
    {
        string p = path + "\\x64\\Debug\\" + argv[i]; //for debugger: path + "\\x64\\Debug\\" + argv[i];
        cout << "File " << i << ": " << p << endl;
        
        try
        {
            if (i == 1)
            {
                //load file
                ifstream file1(p.c_str(), ios::binary);
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
            else if(i == 2) 
            {
                //load file
                ifstream file2(p.c_str(), ios::binary);
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
        }
        catch (const exception ex)
        {
            std::cout << "Error reading file: " << ex.what();
            return 0;
        }
    }

    //compare two files with hamming distance alghoritm
    for (int i = 0; i < maxSize; i++)
    {
        if (i < fileSize1 && i < fileSize2) 
        {
            compData[i] = hammingDistance(dataFile1[i], dataFile2[i]);
        }
        else if (i>fileSize2 && i<=fileSize1) 
        {
            compData[i] = hammingDistance(dataFile1[i], 0);
        }
        else if (i>fileSize1 && i<=fileSize2)
        {
            compData[i] = hammingDistance(0, dataFile2[i]);
        }
        
    }


    cin.get();

}
