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


uint64_t convoluteCalculation(uint16_t k, uint16_t n)
{
    uint64_t result = 0;
    uint32_t hCOeffSign, hCoeffPOT;
    uint16_t xInput;
    int16_t indexOfxData, tmp;
    uint16_t readCurrentBitStatus = 0x0001;
    uint16_t hCoeffPOTStatus = 0x0000, hCOeffSignStatus = 0x0000;
    uint64_t input, inputTwosComplement;

    indexOfxData = n - k;
    if(indexOfxData < 0)
    {
        result = 0;
        return result;
    }
    else
    {
        hCoeffPOT = hCoeff[k] & 0x0000FFFF;
        hCOeffSign = hCoeff[k] & 0xFFFF0000;
        hCOeffSign = hCOeffSign >> 16;
        xInput = xData[indexOfxData];
        tmp = xInput & 0x8000;
        if(tmp == 0x8000)
        {
            input = 0xFFFFFFFFFFFF0000;
        }
        else
        {
            input = 0x0000000000000000;
        }
        input = input | xInput;
        input = input << 16;
        inputTwosComplement = 0 - input;
        for(int i = 0; i <= 15; i++)
        {
            hCoeffPOTStatus = (uint16_t)hCoeffPOT & readCurrentBitStatus;
            hCOeffSignStatus = (uint16_t)hCOeffSign & readCurrentBitStatus;

            if((hCOeffSignStatus != readCurrentBitStatus) && (hCoeffPOTStatus != readCurrentBitStatus))
            {
                if(result == 0)
                {
                    //Do Nothing
                }
                else
                {
                    result = result >> 1;
                }
            }
            else if((hCOeffSignStatus != readCurrentBitStatus) && (hCoeffPOTStatus == readCurrentBitStatus))
            {
                result = result + input;
                result = result >> 1;
            }
            else if((hCOeffSignStatus == readCurrentBitStatus) && (hCoeffPOTStatus != readCurrentBitStatus))
            {
                if(result == 0)
                {
                    //Do Nothing
                }
                else
                {
                    result = result >> 1;
                }
            }
            else
            {
                result = result + inputTwosComplement;
                result = result >> 1;
            }

            readCurrentBitStatus = readCurrentBitStatus << 1;
        }
        return result;
    }
}

#pragma region Convolution Function

/// @brief The function is used to perform convolution for each data set in data.in file and push the result in yOutput vector
void convolutionFunction(std::string filePath)
{
    uint64_t result = 0;
    uint16_t n, k;
    std::vector<uint64_t> yOutput(xData.size(), 0);  //To stroe output data computed from the above two vectors

    for(n = 0; n < xData.size(); n++)
    {
        for(k = 0; k <= 255; k++)
        {
            result = result + convoluteCalculation(k, n);
        }
        yOutput[n] = result;
        result = 0;
    }

    std::ofstream file(filePath);
    for(auto value : yOutput)
    {
        value = value & 0x000000ffffffffff;
        file << std::hex << std::setw(10) << std::setfill('0') << std::uppercase << value << std::endl;
        //file << std::hex << std::uppercase << value << std::endl;
    }
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

    convolutionFunction(argv[3]);

    std::cout << "Convolution result uploaded to file: " << argv[3] << std::endl;

    return 0;

}

#pragma endregion