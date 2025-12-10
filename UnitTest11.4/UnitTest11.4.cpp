#include "pch.h"
#include "CppUnitTest.h"

#include <string>
#include <fstream>
#include <cctype>
#include <sstream>
#include <stdexcept>   // ДЛЯ std::runtime_error
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// ===== СКОПІЙОВАНІ ФУНКЦІЇ З ПРОГРАМИ (ТІ, ЯКІ МИ ТЕСТУЄМО) =====

// Перевірка, чи символ є голосною латинською
bool isVowelChar(char c)
{
    c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return c == 'a' || c == 'e' || c == 'i' ||
        c == 'o' || c == 'u' || c == 'y';
}

// Підрахунок голосних у слові
int countVowelsInWord(const std::string& word)
{
    int count = 0;
    for (char c : word) {
        if (isVowelChar(c)) {
            ++count;
        }
    }
    return count;
}

// Пошук слова з найбільшою кількістю голосних у рядку
std::string findWordWithMostVowels(const std::string& line)
{
    std::string bestWord;
    int bestCount = -1;

    std::string currentWord;

    auto processCurrentWord = [&]() {
        if (!currentWord.empty()) {
            int v = countVowelsInWord(currentWord);
            if (v > bestCount) {
                bestCount = v;
                bestWord = currentWord;
            }
            currentWord.clear();
        }
        };

    for (char c : line) {
        if (std::isalpha(static_cast<unsigned char>(c))) {
            currentWord.push_back(c);
        }
        else {
            processCurrentWord();
        }
    }
    processCurrentWord();

    return bestWord;
}

// Обробка файлу: непарні рядки + слово з найбільшою кількістю голосних, парні — без змін
void processFileToResult(const std::string& sourceFile,
    const std::string& resultFile)
{
    std::ifstream fin(sourceFile);
    if (!fin.is_open()) {
        std::cout << "Cannot open source file: " << sourceFile << "\n";
        return;
    }

    std::ofstream fout(resultFile);
    if (!fout.is_open()) {
        std::cout << "Cannot open result file: " << resultFile << "\n";
        return;
    }

    std::string line;
    int lineNumber = 0;

    while (std::getline(fin, line)) {
        ++lineNumber;

        if (lineNumber % 2 == 1) {
            std::string bestWord = findWordWithMostVowels(line);
            if (!bestWord.empty()) {
                fout << line << ' ' << bestWord << '\n';
            }
            else {
                fout << line << '\n';
            }
        }
        else {
            fout << line << '\n';
        }
    }
}

// ===== ДОПОМІЖНІ ФУНКЦІЇ ДЛЯ ТЕСТІВ =====

// Зручне порівняння std::string через MSTest
void AssertStringsEqual(const std::string& expected, const std::string& actual)
{
    std::wstring wexp(expected.begin(), expected.end());
    std::wstring wact(actual.begin(), actual.end());
    Assert::AreEqual(wexp.c_str(), wact.c_str());
}

// Запис тестового файлу
void writeTestFile(const std::string& fileName, const std::string& content)
{
    std::ofstream fout(fileName);
    if (!fout.is_open()) {
        throw std::runtime_error("Cannot open test file: " + fileName);
    }
    fout << content;
}

// Читання всього файлу в один рядок (тільки для тестів)
std::string readWholeFile(const std::string& fileName)
{
    std::ifstream fin(fileName);
    if (!fin.is_open()) {
        throw std::runtime_error("Cannot open test file: " + fileName);
    }
    return std::string((std::istreambuf_iterator<char>(fin)),
        std::istreambuf_iterator<char>());
}

// ===== ВЛАСНЕ ЮНІТ-ТЕСТИ =====

namespace LineProcessingTests
{
    TEST_CLASS(VowelTests)
    {
    public:
        TEST_METHOD(IsVowelChar_Basic)
        {
            Assert::IsTrue(isVowelChar('a'));
            Assert::IsTrue(isVowelChar('E'));
            Assert::IsTrue(isVowelChar('y'));
            Assert::IsFalse(isVowelChar('b'));
            Assert::IsFalse(isVowelChar('Z'));
            Assert::IsFalse(isVowelChar('1'));
        }

        TEST_METHOD(CountVowelsInWord_Basic)
        {
            Assert::AreEqual(2, countVowelsInWord("apple"));   // a, e
            Assert::AreEqual(1, countVowelsInWord("sky"));     // y
            Assert::AreEqual(0, countVowelsInWord("brrrp"));   // жодної голосної
        }
    };

    TEST_CLASS(FindWordWithMostVowelsTests)
    {
    public:
        TEST_METHOD(FindWordWithMostVowels_SimpleLine)
        {
            std::string line = "This is apple orange";
            // This(1), is(1), apple(2), orange(3) -> orange
            std::string best = findWordWithMostVowels(line);
            AssertStringsEqual("orange", best);
        }

        TEST_METHOD(FindWordWithMostVowels_TieReturnsFirst)
        {
            std::string line = "see bee tree";
            // see(2), bee(2), tree(2) -> перше з макс. к-стю = "see"
            std::string best = findWordWithMostVowels(line);
            AssertStringsEqual("see", best);
        }

        TEST_METHOD(FindWordWithMostVowels_NoWords)
        {
            std::string line = "1234 !!!";
            std::string best = findWordWithMostVowels(line);
            AssertStringsEqual("", best);
        }
    };

    TEST_CLASS(ProcessFileTests)
    {
    public:
        TEST_METHOD(ProcessFile_OddEvenLines)
        {
            const std::string srcFile = "test_source.txt";
            const std::string resFile = "test_result.txt";

            // Створимо вихідний файл:
            // 1: odd  -> find best word, append at end
            // 2: even -> copy as is
            // 3: odd  -> find best word, append
            std::string srcContent;
            srcContent += "This is apple orange\n"; // odd: best = orange
            srcContent += "Second line text\n";     // even
            srcContent += "Sky by my\n";            // odd: Sky(1), by(1), my(1) -> Sky

            writeTestFile(srcFile, srcContent);

            // Викликаємо обробку
            processFileToResult(srcFile, resFile);

            // Читаємо результат
            std::string result = readWholeFile(resFile);

            // Очікуваний вміст:
            // 1: "This is apple orange orange\n"
            // 2: "Second line text\n"
            // 3: "Sky by my Sky\n"
            std::string expected;
            expected += "This is apple orange orange\n";
            expected += "Second line text\n";
            expected += "Sky by my Sky\n";

            AssertStringsEqual(expected, result);
        }
    };
}
