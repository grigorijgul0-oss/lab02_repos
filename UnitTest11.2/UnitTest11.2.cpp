#include "pch.h"
#include "CppUnitTest.h"

#include <string>
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// ===== КОПІЇ ФУНКЦІЙ З ПРОГРАМИ (АБО ЇХ СПРОЩЕНІ АНАЛОГИ) =====

// Функція нормалізує пробіли в тексті
// (повністю повторює алгоритм з твоєї програми)
std::string normalizeSpaces(const std::string& text)
{
    std::string result;
    result.reserve(text.size());

    std::size_t i = 0;
    std::size_t n = text.size();

    // Пропускаємо початкові пробіли
    while (i < n && text[i] == ' ')
        i++;

    bool hasPendingSpace = false;

    for (; i < n; i++) {
        char c = text[i];

        if (c == ' ') {
            hasPendingSpace = true;
        }
        else {
            if (hasPendingSpace && !result.empty()) {
                result.push_back(' ');
            }
            hasPendingSpace = false;
            result.push_back(c);
        }
    }

    // кінцеві пробіли не додаються, бо ми їх не записуємо
    return result;
}

// Допоміжна функція для тестів: запис у файл
void writeFileForTest(const std::string& fileName, const std::string& content)
{
    std::ofstream fout(fileName);
    if (!fout.is_open()) {
        throw std::runtime_error("Cannot open file for test: " + fileName);
    }
    fout << content;
}

// Допоміжна функція для тестів: читання з файлу
std::string readFileForTest(const std::string& fileName)
{
    std::ifstream fin(fileName);
    if (!fin.is_open()) {
        throw std::runtime_error("Cannot open file for test: " + fileName);
    }
    std::string data((std::istreambuf_iterator<char>(fin)),
        std::istreambuf_iterator<char>());
    return data;
}

// Допоміжна функція: порівняння std::string через MSTest (через wstring)
void AssertStringsEqual(const std::string& expected, const std::string& actual)
{
    std::wstring wexp(expected.begin(), expected.end());
    std::wstring wact(actual.begin(), actual.end());
    Assert::AreEqual(wexp.c_str(), wact.c_str());
}

// ===== ВЛАСНЕ ЮНІТ-ТЕСТИ =====

namespace UnitTestNormalizeSpaces
{
    TEST_CLASS(NormalizeSpacesTests)
    {
    public:

        // Жодних зайвих пробілів — рядок має лишитися без змін
        TEST_METHOD(NoExtraSpaces_ShouldStaySame)
        {
            std::string input = "Hello world!";
            std::string expected = "Hello world!";

            std::string actual = normalizeSpaces(input);

            AssertStringsEqual(expected, actual);
        }

        // Початкові і кінцеві пробіли видаляються
        TEST_METHOD(LeadingAndTrailingSpaces_Removed)
        {
            std::string input = "   Hello world!   ";
            std::string expected = "Hello world!";

            std::string actual = normalizeSpaces(input);

            AssertStringsEqual(expected, actual);
        }

        // Внутрішня група пробілів зводиться до одного
        TEST_METHOD(InnerMultipleSpaces_CompressedToOne)
        {
            std::string input = "Hello   world   !!!";
            std::string expected = "Hello world !!!";

            std::string actual = normalizeSpaces(input);

            AssertStringsEqual(expected, actual);
        }

        // Тільки пробіли навколо одного слова
        TEST_METHOD(OnlySpacesAroundWord)
        {
            std::string input = "     word     ";
            std::string expected = "word";

            std::string actual = normalizeSpaces(input);

            AssertStringsEqual(expected, actual);
        }

        // Перевірка з кількома рядками і пробілами перед/після
        TEST_METHOD(MultiLineText_SpacesNormalized)
        {
            // Тут \n - символ нового рядка, він не чіпається.
            std::string input =
                "   line1   \n"
                "  line2   here  ";

            // Пояснення:
            // - початкові пробіли перед "line1" прибираються
            // - після "line1" перед \n лишається один пробіл
            // - початкові пробіли перед "line2" замінюються на один внутрішній пробіл
            // - "   " між "line2" і "here" -> один пробіл
            // - кінцеві пробіли після "here" прибираються
            std::string expected =
                "line1 \n"
                " line2 here";

            std::string actual = normalizeSpaces(input);

            AssertStringsEqual(expected, actual);
        }

        // Інтеграційний тест: "файловий" сценарій t1 -> t2
        TEST_METHOD(FileIntegration_NormalizeSpaces)
        {
            const std::string t1 = "test_t1.txt";
            const std::string t2 = "test_t2.txt";

            std::string input =
                "   This   is   a   test   \n"
                "   with    spaces   ";

            // Очікуваний нормалізований текст:
            std::string expected =
                "This is a test \n"
                " with spaces";

            // 1. Записуємо "t1"
            writeFileForTest(t1, input);

            // 2. Читаємо t1 (як робить твоя програма)
            std::string original = readFileForTest(t1);

            // 3. Нормалізуємо
            std::string normalized = normalizeSpaces(original);

            // 4. Записуємо t2
            writeFileForTest(t2, normalized);

            // 5. Читаємо t2 і порівнюємо з expected
            std::string fromFile = readFileForTest(t2);

            AssertStringsEqual(expected, fromFile);
        }
    };
}
