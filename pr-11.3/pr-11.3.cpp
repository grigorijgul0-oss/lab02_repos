#include <iostream>
#include <fstream>
#include <string>

// ---------- Допоміжні функції для введення ----------

// Виводить меню
void printMenu()
{
    std::cout << "\n===== MENU =====\n"
        << "1. Create schedule file (overwrite)\n"
        << "2. View schedule file\n"
        << "3. Append trains to file\n"
        << "4. Show trains departing after given time\n"
        << "5. Exit\n"
        << "Your choice: ";
}

// Зчитує число з перевіркою діапазону
int readIntInRange(int minValue, int maxValue)
{
    while (true) {
        std::string line;
        std::getline(std::cin, line);

        try {
            int value = std::stoi(line);
            if (value < minValue || value > maxValue) {
                std::cout << "Enter a number between " << minValue
                    << " and " << maxValue << ": ";
                continue;
            }
            return value;
        }
        catch (...) {
            std::cout << "Invalid input. Enter a number between "
                << minValue << " and " << maxValue << ": ";
        }
    }
}

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

// Зчитування часу у форматі HH:MM з клавіатури
void readTimeFromUser(int& hour, int& minute)
{
    while (true) {
        std::cout << "Enter time (HH:MM): ";
        std::string t;
        std::getline(std::cin, t);

        if (parseTimeString(t, hour, minute))
            return;

        std::cout << "Invalid format.\n";
    }
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

// ---------- Операції з одним записом ----------

// Зчитування одного запису поїзда з клавіатури
bool readTrainFromUser(std::string& destination,
    std::string& type,
    int& hour,
    int& minute)
{
    std::cout << "Enter destination (empty = cancel): ";
    std::getline(std::cin, destination);
    if (destination.empty())
        return false;

    std::cout << "Select train type:\n"
        << "1. regular\n"
        << "2. comfort\n"
        << "3. express\n"
        << "Your choice: ";
    int choice = readIntInRange(1, 3);

    if (choice == 1) type = "regular";
    else if (choice == 2) type = "comfort";
    else type = "express";

    readTimeFromUser(hour, minute);
    return true;
}

// Запис одного поїзда у файл
void writeTrainToStream(std::ofstream& fout,
    const std::string& dest,
    const std::string& type,
    int hour,
    int minute)
{
    // Формат запису: destination|type|HH:MM
    fout << dest << "|" << type << "|" << formatTime(hour, minute) << "\n";
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

// ---------- Операції з файлом ----------

// Створення файлу розкладу (перезапис)
void createScheduleFile(const std::string& fileName)
{
    std::ofstream fout(fileName);
    if (!fout.is_open()) {
        std::cout << "Cannot open file: " << fileName << "\n";
        return;
    }

    std::cout << "Creating schedule file. Enter trains.\n"
        << "Empty destination = stop.\n";

    while (true) {
        std::string dest, type;
        int h, m;

        if (!readTrainFromUser(dest, type, h, m)) {
            std::cout << "Input finished.\n";
            break;
        }

        writeTrainToStream(fout, dest, type, h, m);
    }
}

// Доповнення файлу новими записами
void appendScheduleFile(const std::string& fileName)
{
    std::ofstream fout(fileName, std::ios::app);
    if (!fout.is_open()) {
        std::cout << "Cannot open file: " << fileName << "\n";
        return;
    }

    std::cout << "Appending trains. Empty destination = stop.\n";

    while (true) {
        std::string dest, type;
        int h, m;

        if (!readTrainFromUser(dest, type, h, m)) {
            std::cout << "Input finished.\n";
            break;
        }

        writeTrainToStream(fout, dest, type, h, m);
    }
}

// Перегляд файлу розкладу
void viewScheduleFile(const std::string& fileName)
{
    std::ifstream fin(fileName);
    if (!fin.is_open()) {
        std::cout << "Cannot open file: " << fileName << "\n";
        return;
    }

    std::cout << "\n===== CONTENT OF " << fileName << " =====\n";

    std::string line;
    bool any = false;

    while (std::getline(fin, line)) {
        if (line.empty()) continue;

        std::string dest, type;
        int h, m;

        if (parseTrainLine(line, dest, type, h, m)) {
            printTrain(dest, type, h, m);
            any = true;
        }
        else {
            std::cout << "Invalid line: " << line << "\n";
        }
    }

    if (!any)
        std::cout << "(file empty)\n";

    std::cout << "====================================\n";
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

// ---------- Головна програма ----------

int main()
{
    std::cout << "Enter schedule file name (e.g., trains.txt): ";
    std::string fileName;
    std::getline(std::cin, fileName);

    if (fileName.empty()) {
        std::cout << "File name cannot be empty.\n";
        return 0;
    }

    while (true) {
        printMenu();
        int choice = readIntInRange(1, 5);

        if (choice == 1) {
            createScheduleFile(fileName);
        }
        else if (choice == 2) {
            viewScheduleFile(fileName);
        }
        else if (choice == 3) {
            appendScheduleFile(fileName);
        }
        else if (choice == 4) {
            int h, m;
            readTimeFromUser(h, m);
            showTrainsAfter(fileName, h, m);
        }
        else if (choice == 5) {
            std::cout << "Exiting program.\n";
            break;
        }
    }

    return 0;
}
