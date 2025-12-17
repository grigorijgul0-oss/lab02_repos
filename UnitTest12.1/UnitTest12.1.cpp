#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include <vector>
#include "../pr-12.1 c++/FileFunctions.cpp" // Вкажіть правильний шлях до заголовка

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MyProjectTests
{
    TEST_CLASS(FileProcessingTests)
    {
    public:

        // Тест 1: Перевірка математичної логіки
        TEST_METHOD(TestIsCosineValue)
        {
            // Перевірка правильних значень (-1, 0, 1)
            Assert::IsTrue(isCosineValue(-1), L"Failed on -1");
            Assert::IsTrue(isCosineValue(0), L"Failed on 0");
            Assert::IsTrue(isCosineValue(1), L"Failed on 1");

            // Перевірка неправильних значень
            Assert::IsFalse(isCosineValue(-5), L"Failed on -5");
            Assert::IsFalse(isCosineValue(2), L"Failed on 2");
            Assert::IsFalse(isCosineValue(100), L"Failed on 100");
        }

        // Тест 2: Інтеграційний тест (робота з файлами)
        TEST_METHOD(TestFilterDataToFile)
        {
            std::string inFile = "test_input.txt";
            std::string outFile = "test_output.txt";

            // 1. Створюємо вхідний файл
            std::ofstream tempIn(inFile);
            // Записуємо: -2 (ні), -1 (так), 0 (так), 5 (ні)
            tempIn << "-2 -1 0 5";
            tempIn.close();

            // 2. Викликаємо функцію
            filterDataToFile(inFile, outFile);

            // 3. Перевіряємо результат
            std::ifstream tempOut(outFile);
            std::vector<int> results;
            int num;
            while (tempOut >> num) {
                results.push_back(num);
            }
            tempOut.close();

            // 4. Asserts (Твердження)
            // Має залишитися тільки два числа: -1 та 0
            Assert::AreEqual((size_t)2, results.size(), L"Wrong count of numbers");
            Assert::AreEqual(-1, results[0], L"First number matches");
            Assert::AreEqual(0, results[1], L"Second number matches");

            // 5. Очищення
            remove(inFile.c_str());
            remove(outFile.c_str());
        }
    };
}