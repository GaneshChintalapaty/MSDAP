#pragma region Headers

//Include all required header files here
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <bitset>
#include <sstream>
#include <string>
#include <iomanip>
#include <stdint.h>
#include <fstream>
#include <vector>

#pragma endregion

#pragma region Global Variables

//Include Vector variables here
std::vector<int> hCoeff;
std::vector<int> xData;
std::vector<int> yOutput;
//End Vector variables

#pragma endregion

#pragma region Parse Algorithm

int parse(std::string filePath, uint8_t selectVectorToStoreData)
{
    std::ifstream inputFile(filePath);
}

#pragma endregion

#pragma region Main Function

int main(int argc, char *argv[])
{
    if(argc != 4)
    {
        std::cerr << "Usage: " << argv[0] << "<path/to/coeff.in> <path/to/data.in> <path/to/output.out>\n";
        return 1;
    }

    int fileParseStatus;

    fileParseStatus = parse(argv[1], 1);

}

#pragma endregion