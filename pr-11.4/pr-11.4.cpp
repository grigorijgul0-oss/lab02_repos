#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

// --------- Допоміжні функції введення / виведення ----------

// Вивід меню
void printMenu()
{
    std::cout << "\n===== MENU =====\n"
        << "1. Create source file and write lines (overwrite)\n"
        << "2. View source file\n"
        << "3. Process source file and create result file\n"
        << "4. View result file\n"
        << "5. Exit\n"
        << "Your choice: ";
}

// Зчитування цілого з контролем діапазону
int readIntInRange(int minValue, int maxValue)
{
    while (true) {
        std::string line;
        std::getline(std::cin, line);

        try {
            int value = std::stoi(line);
            if (value < minValue || value > maxValue) {
                std::cout << "Enter a number between "
                    << minValue << " and " << maxValue << ": ";
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

// Зчитування рядка-імені файлу з контролем порожнього вводу
std::string readFileNameFromUser(const std::string& prompt)
{
    while (true) {
        std::cout << prompt;
        std::string name;
        std::getline(std::cin, name);
        if (!name.empty())
            return name;
        std::cout << "File name cannot be empty.\n";
    }
}

// --------- Робота з файлом: створення, перегляд ----------

// Створення (перезапис) вихідного файлу: зчитування рядків з клавіатури
// Порожній рядок = кінець введення
void createSourceFile(const std::string& fileName)
{
    std::ofstream fout(fileName);
    if (!fout.is_open()) {
        std::cout << "Cannot open file: " << fileName << "\n";
        return;
    }

    std::cout << "Enter lines to write to file \"" << fileName << "\".\n"
        << "Empty line = finish.\n";

    std::string line;
    while (true) {
        std::getline(std::cin, line);
        if (line.empty())
            break;
        fout << line << '\n';
    }

    std::cout << "Source file created.\n";
}

// Перегляд файлу (пострічковий вивід)
void viewFile(const std::string& fileName)
{
    std::ifstream fin(fileName);
    if (!fin.is_open()) {
        std::cout << "Cannot open file: " << fileName << "\n";
        return;
    }

    std::cout << "\n===== CONTENT OF \"" << fileName << "\" =====\n";

    std::string line;
    bool any = false;
    while (std::getline(fin, line)) {
        any = true;
        std::cout << line << '\n';
    }

    if (!any) {
        std::cout << "(file is empty)\n";
    }

    std::cout << "====================================\n";
}

// --------- Допоміжні функції для роботи зі словами ----------

// Перевірка, чи символ є голосною латинською (можеш додати свої при потребі)
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

// Пошук слова з найбільшою кількістю голосних у рядку.
// Слово визначаємо як послідовність alphabetic-символів.
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
    // обробка останнього слова в кінці рядка
    processCurrentWord();

    return bestWord; // може бути порожнім, якщо слів нема
}

// --------- Обробка файлу згідно умови ----------

// Обробка вихідного файлу і запис у новий файл:
// - парні рядки: переписуються без змін;
// - непарні рядки: в кінець дописується слово з найбільшою кількістю голосних
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
        ++lineNumber; // перший рядок = 1 (непарний)

        if (lineNumber % 2 == 1) {
            // непарний рядок: знайти слово з найбільшою кількістю голосних
            std::string bestWord = findWordWithMostVowels(line);
            if (!bestWord.empty()) {
                fout << line << ' ' << bestWord << '\n';
            }
            else {
                // якщо слів немає — просто записати рядок
                fout << line << '\n';
            }
        }
        else {
            // парний рядок: переписати як є
            fout << line << '\n';
        }
    }

    std::cout << "Result file \"" << resultFile << "\" created.\n";
}

// --------- Головна функція ----------

int main()
{
    // Ім'я вихідного файлу (з рядками, введеними з клавіатури)
    std::string sourceFileName = readFileNameFromUser(
        "Enter source file name (e.g., source.txt): "
    );

    // Ім'я результатного файлу (з дописаними словами)
    std::string resultFileName = readFileNameFromUser(
        "Enter result file name (e.g., result.txt): "
    );

    while (true) {
        printMenu();
        int choice = readIntInRange(1, 5);

        if (choice == 1) {
            // Створити та заповнити вихідний файл
            createSourceFile(sourceFileName);
        }
        else if (choice == 2) {
            // Переглянути вихідний файл
            viewFile(sourceFileName);
        }
        else if (choice == 3) {
            // Обробити файл: створити новий з дописаними словами
            processFileToResult(sourceFileName, resultFileName);
        }
        else if (choice == 4) {
            // Переглянути результатний файл
            viewFile(resultFileName);
        }
        else if (choice == 5) {
            std::cout << "Exiting program.\n";
            break;
        }
    }

    return 0;
}
