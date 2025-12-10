#include "pch.h"
#include "CppUnitTest.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// ===== СКОПІЙОВАНІ ФУНКЦІЇ З ПРОГРАМИ (ДЛЯ ТЕСТІВ) =====

// Перевірка та розбір формату часу HH:MM
bool parseTimeString(const std::string& timeStr, int& hour, int& minute)
{
    if (timeStr.size() != 5 || timeStr[2] != ':')
        return false;

    std::string hStr = timeStr.substr(0, 2);
    std::string mStr = timeStr.substr(3, 2);

    try {
        hour = std::stoi(hStr);
        minute = std::stoi(mStr);
    }
    catch (...) {
        return false;
    }

    return (hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59);
}

// Формує рядок часу HH:MM
std::string formatTime(int hour, int minute)
{
    std::string r;
    if (hour < 10) r += '0';
    r += std::to_string(hour);
    r += ':';
    if (minute < 10) r += '0';
    r += std::to_string(minute);
    return r;
}

// Порівняння часу: чи поїзд відправляється пізніше
bool isTrainAfterTime(int th, int tm, int rh, int rm)
{
    if (th > rh) return true;
    if (th < rh) return false;
    return tm > rm;
}

// Парсинг рядка з файлу
bool parseTrainLine(const std::string& line,
    std::string& dest,
    std::string& type,
    int& hour,
    int& minute)
{
    size_t p1 = line.find('|');
    if (p1 == std::string::npos) return false;

    size_t p2 = line.find('|', p1 + 1);
    if (p2 == std::string::npos) return false;

    dest = line.substr(0, p1);
    type = line.substr(p1 + 1, p2 - p1 - 1);

    std::string timeStr = line.substr(p2 + 1);
    return parseTimeString(timeStr, hour, minute);
}

// Виведення одного поїзда
void printTrain(const std::string& dest,
    const std::string& type,
    int hour,
    int minute)
{
    std::cout << "Destination: " << dest
        << " | Type: " << type
        << " | Departure: " << formatTime(hour, minute) << "\n";
}

// Вивід поїздів, які відправляються пізніше за вказаний час
void showTrainsAfter(const std::string& fileName, int rh, int rm)
{
    std::ifstream fin(fileName);
    if (!fin.is_open()) {
        std::cout << "Cannot open file: " << fileName << "\n";
        return;
    }

    std::cout << "\nTrains departing after " << formatTime(rh, rm) << ":\n";

    std::string line;
    bool found = false;

    while (std::getline(fin, line)) {
        if (line.empty()) continue;

        std::string dest, type;
        int h, m;

        if (!parseTrainLine(line, dest, type, h, m))
            continue;

        if (isTrainAfterTime(h, m, rh, rm)) {
            printTrain(dest, type, h, m);
            found = true;
        }
    }

    if (!found)
        std::cout << "No trains found.\n";
}

// ===== ДОПОМІЖНІ ФУНКЦІЇ ДЛЯ ТЕСТІВ =====

// Зручне порівняння std::string через MSTest (через wstring)
void AssertStringsEqual(const std::string& expected, const std::string& actual)
{
    std::wstring wexp(expected.begin(), expected.end());
    std::wstring wact(actual.begin(), actual.end());
    Assert::AreEqual(wexp.c_str(), wact.c_str());
}

// Створення тестового файлу з заданим вмістом
void writeTestFile(const std::string& fileName, const std::string& content)
{
    std::ofstream fout(fileName);
    if (!fout.is_open()) {
        throw std::runtime_error("Cannot open test file: " + fileName);
    }
    fout << content;
}

// Читання всього файлу в рядок (тільки для тестів)
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

namespace TrainScheduleTests
{
    TEST_CLASS(TimeParseTests)
    {
    public:
        TEST_METHOD(ParseTime_Valid)
        {
            int h = -1, m = -1;
            bool ok = parseTimeString("09:30", h, m);
            Assert::IsTrue(ok);
            Assert::AreEqual(9, h);
            Assert::AreEqual(30, m);
        }

        TEST_METHOD(ParseTime_InvalidFormat)
        {
            int h, m;
            Assert::IsFalse(parseTimeString("9:30", h, m));    // не 2 цифри
            Assert::IsFalse(parseTimeString("0930", h, m));    // без двокрапки
            Assert::IsFalse(parseTimeString("aa:bb", h, m));   // букви
            Assert::IsFalse(parseTimeString("25:00", h, m));   // година > 23
            Assert::IsFalse(parseTimeString("10:99", h, m));   // хвилини > 59
        }
    };

    TEST_CLASS(FormatTimeTests)
    {
    public:
        TEST_METHOD(FormatTime_LeadingZeros)
        {
            std::string t1 = formatTime(9, 5);
            std::string t2 = formatTime(13, 45);

            AssertStringsEqual("09:05", t1);
            AssertStringsEqual("13:45", t2);
        }
    };

    TEST_CLASS(TimeCompareTests)
    {
    public:
        TEST_METHOD(IsTrainAfterTime_Basic)
        {
            // 10:00 > 09:59
            Assert::IsTrue(isTrainAfterTime(10, 0, 9, 59));
            // 10:00 не > 10:00
            Assert::IsFalse(isTrainAfterTime(10, 0, 10, 0));
            // 10:01 > 10:00
            Assert::IsTrue(isTrainAfterTime(10, 1, 10, 0));
            // 09:59 не > 10:00
            Assert::IsFalse(isTrainAfterTime(9, 59, 10, 0));
        }
    };

    TEST_CLASS(ParseTrainLineTests)
    {
    public:
        TEST_METHOD(ParseTrainLine_Valid)
        {
            std::string line = "Kyiv|express|06:30";
            std::string dest, type;
            int h, m;

            bool ok = parseTrainLine(line, dest, type, h, m);
            Assert::IsTrue(ok);
            AssertStringsEqual("Kyiv", dest);
            AssertStringsEqual("express", type);
            Assert::AreEqual(6, h);
            Assert::AreEqual(30, m);
        }

        TEST_METHOD(ParseTrainLine_Invalid)
        {
            std::string dest, type;
            int h, m;

            // немає розділювачів
            Assert::IsFalse(parseTrainLine("Kyiv 06:30", dest, type, h, m));
            // час у неправильному форматі
            Assert::IsFalse(parseTrainLine("Kyiv|express|6:30", dest, type, h, m));
        }
    };

    TEST_CLASS(ShowTrainsAfterTests)
    {
    public:
        TEST_METHOD(ShowTrainsAfter_FiltersCorrectly)
        {
            const std::string fileName = "test_trains.txt";

            // Готуємо файл:
            // - 06:30
            // - 10:00
            // - 15:45
            std::string content;
            content += "Kyiv|regular|06:30\n";
            content += "Lviv|express|10:00\n";
            content += "Odessa|comfort|15:45\n";

            writeTestFile(fileName, content);

            // Перенаправляємо std::cout у буфер
            std::ostringstream oss;
            std::streambuf* oldBuf = std::cout.rdbuf(oss.rdbuf());

            // Показуємо поїзди після 09:00 -> очікуємо Lviv і Odessa
            showTrainsAfter(fileName, 9, 0);

            // Повертаємо cout назад
            std::cout.rdbuf(oldBuf);

            std::string output = oss.str();

            // Перевіряємо, що є потрібні рядки
            Assert::IsTrue(output.find("Lviv") != std::string::npos);
            Assert::IsTrue(output.find("Odessa") != std::string::npos);
            // І поїзд о 06:30 не має бути виведений
            Assert::IsTrue(output.find("Kyiv|regular|06:30") == std::string::npos);
        }
    };
}
