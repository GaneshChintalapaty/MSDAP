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
std::vector<uint32_t> hCoeff;   //To store data from coeff.in
std::vector<uint16_t> xData;    //To store data from data.in
std::vector<uint64_t> yOutput;  //To stroe output data computed from the above two vectors
//End Vector variables

#pragma endregion

#pragma region Parse Algorithm

/// @brief The following funtion is used to parse the docuemnt and read the hex numbers in the given file path and store the data in the desired globally initilized vectors
/// @param filePath variable type = string
/// @param selectVectorToStoreData variable type = uint8_t
/// @return 0 - if no error else 1
int parse(std::string filePath, uint8_t selectVectorToStoreData)
{
    std::ifstream inputFile(filePath);  //Input file path

    if(inputFile.is_open()) //If file open
    {
        std::string line;   //string to store data to process
        while(std::getline(inputFile, line))    //Read each line till the end of file
        {
            std::istringstream iss(line);   //To convert string to hex number
            std::string hexString;
            iss >> hexString;

            switch (selectVectorToStoreData)
            {
            case 1: //Store data to hCoeff
                {
                    uint32_t hexCoeff;
                    std::stringstream(hexString) >> std::hex >> hexCoeff;   //Convert to hex
                    hCoeff.push_back(hexCoeff); //Add data at the end of the vector
                }
                break;
            case 2: //Store data to xData
                {
                    uint16_t hexData;
                    std::stringstream(hexString) >> std::hex >>hexData; //Convert to hex
                    xData.push_back(hexData);   //Add data at the end of the vector
                }
                break;
            
            default:    //Do nothing
                break;
            }
        }
        inputFile.close();  //Close file
    }
    else    //If file not open
    {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }
    return 0;
}

#pragma endregion

#pragma region Main Function

/// @brief Main Function to accept three files namely coeff, data and output. Compute the convolution from coeff and data and store it in output
/// @param argc 
/// @param argv 
/// @return 0 - if no error else 1
int main(int argc, char *argv[])
{
    if(argc != 4)
    {
        std::cerr << "Usage: " << argv[0] << "<path/to/coeff.in> <path/to/data.in> <path/to/output.out>\n";
        return 1;
    }

    int fileParseStatus;    //Variable to store the parsing status

    fileParseStatus = parse(argv[1], 1);    //Parse coeff.in file

    if(fileParseStatus == 1)    //If failed to parse file end program
    {
        return 1;
    }

    fileParseStatus = parse(argv[2], 2);    //Parse data.in file

    if(fileParseStatus == 1)    //If failed to parse the file end program
    {
        return 1;
    }

    return 0;

}

#pragma endregion