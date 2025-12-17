#include "FileFunctions.h"
#include <fstream>

bool isCosineValue(int number) {
    return (number >= -1 && number <= 1);
}

void filterDataToFile(const std::string& inputFilename, const std::string& outputFilename) {
    std::ifstream inFile(inputFilename);
    std::ofstream outFile(outputFilename);

    if (!inFile.is_open() || !outFile.is_open()) return;

    int number;
    while (inFile >> number) {
        if (isCosineValue(number)) {
            outFile << number << " ";
        }
    }
    // Файли закриються автоматично деструкторами, але можна явно:
    inFile.close();
    outFile.close();
}