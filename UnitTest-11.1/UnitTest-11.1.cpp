#include "pch.h"
#include "CppUnitTest.h"

#include <fstream>
#include <string>
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// ---------- Реалізація твоєї функції countCommaDash ----------
int countCommaDash(const std::string& fileName)
{
    std::ifstream fin(fileName);
    if (!fin.is_open()) {
        std::cout << "Cannot open file: " << fileName << std::endl;
        return 0;
    }

    int count = 0;
    std::string line;

    while (std::getline(fin, line)) {
        for (std::size_t j = 0; j + 1 < line.size(); ++j) {
            if (line[j] == ',' && line[j + 1] == '-') {
                ++count;
            }
        }
    }

    return count;
}
// ---------------------------------------------------------------

// Допоміжна функція створення тестових файлів
void writeToFile(const std::string& fileName, const std::string& content)
{
    std::ofstream fout(fileName);
    fout << content;
}

namespace UnitTestCommaDash
{
    TEST_CLASS(CommaDashTests)
    {
    public:

        TEST_METHOD(TestEmptyFile)
        {
            writeToFile("test_empty.txt", "");

            int result = countCommaDash("test_empty.txt");
            Assert::AreEqual(0, result);
        }

        TEST_METHOD(TestNoCommaDash)
        {
            writeToFile("test_no.txt", "abc def-ghi");

            int result = countCommaDash("test_no.txt");
            Assert::AreEqual(0, result);
        }

        TEST_METHOD(TestOneCommaDash)
        {
            writeToFile("test_one.txt", "Hello,-world");

            int result = countCommaDash("test_one.txt");
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestTwoCommaDashSameLine)
        {
            writeToFile("test_two.txt", ",-,-");

            int result = countCommaDash("test_two.txt");
            Assert::AreEqual(2, result);
        }

        TEST_METHOD(TestMultipleLines)
        {
            writeToFile("test_multiline.txt",
                "text,- in line1\n"
                ",- in line2\n"
            );

            int result = countCommaDash("test_multiline.txt");
            Assert::AreEqual(2, result);
        }
    };
}
