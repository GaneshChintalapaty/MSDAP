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
std::vector<uint32_t> hCoeff;
std::vector<uint16_t> xData;
std::vector<uint64_t> yOutput;
//End Vector variables

#pragma endregion

#pragma region Parse Algorithm

int parse(std::string filePath, uint8_t selectVectorToStoreData)
{
    std::ifstream inputFile(filePath);

    if(inputFile.is_open())
    {
        std::string line;
        while(std::getline(inputFile, line))
        {
            std::istringstream iss(line);
            std::string hexString;
            iss >> hexString;

            switch (selectVectorToStoreData)
            {
            case 1:
                {
                    uint32_t hexCoeff;
                    std::stringstream(hexString) >> std::hex >> hexCoeff;
                    hCoeff.push_back(hexCoeff);
                }
                break;
            case 2:
                {
                    uint16_t hexData;
                    std::stringstream(hexString) >> std::hex >>hexData;
                    xData.push_back(hexData);
                }
                break;
            
            default:
                break;
            }
        }
        inputFile.close();

        std::cout << "Hex numbers stored in hCoeff:" << std::endl;

        for(int num : hCoeff)
        {
            std::cout << std::hex << num << std::endl;
        }

        std::cout << "Hex numbers stored in xData:" << std::endl;

        for(int num : xData)
        {
            std::cout << std::hex << num << std::endl;
        }

    }
    else
    {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }
    return 0;
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

    if(fileParseStatus == 1)
    {
        return 1;
    }

    fileParseStatus = parse(argv[2], 2);

    if(fileParseStatus == 1)
    {
        return 1;
    }

    return 0;

}

#pragma endregion