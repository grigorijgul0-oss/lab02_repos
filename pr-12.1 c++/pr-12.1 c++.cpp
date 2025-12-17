#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

// Прототипи функцій
std::string getFileNameFromUser(const std::string& prompt);
bool isCosineValue(int number);
void generateDataFile(const std::string& filename, int count);
void filterDataToFile(const std::string& inputFilename, const std::string& outputFilename);
void displayFileContent(const std::string& filename);

int main() {
    // Налаштування генератора випадкових чисел та локалізації
    std::srand(static_cast<unsigned int>(std::time(0)));
    setlocale(LC_ALL, "uk_UA.UTF-8");

    // 1. Введення імен файлів
    std::string inputFileName = getFileNameFromUser("Введіть ім'я вхідного файлу (наприклад, data.txt): ");
    std::string outputFileName = getFileNameFromUser("Введіть ім'я вихідного файлу (наприклад, result.txt): ");

    // 2. Формування вхідного файлу
   
    generateDataFile(inputFileName, 20);

    std::cout << "\n--- Вміст початкового файлу ---" << std::endl;
    displayFileContent(inputFileName);

    // 3. Опрацювання даних (фільтрація)
    filterDataToFile(inputFileName, outputFileName);

    // 4. Вивід результатів
    std::cout << "\n--- Вміст результуючого файлу (значення cos x) ---" << std::endl;
    displayFileContent(outputFileName);

    return 0;
}


std::string getFileNameFromUser(const std::string& prompt) {
    std::string filename;
    std::cout << prompt;
    std::cin >> filename;
    return filename;
}

bool isCosineValue(int number) {
    // cos(x) завжди в межах [-1, 1].
    // Для цілих чисел це тільки: -1, 0, 1.
    return (number >= -1 && number <= 1);
}

void generateDataFile(const std::string& filename, int count) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Помилка: Не вдалося створити файл " << filename << std::endl;
        return;
    }

    // Генеруємо числа в діапазоні від -5 до 5, щоб часто траплялися -1, 0, 1
    for (int i = 0; i < count; ++i) {
        int randomNum = (std::rand() % 11) - 5;
        file << randomNum << " ";
    }

    file.close();
}


void filterDataToFile(const std::string& inputFilename, const std::string& outputFilename) {
    std::ifstream inFile(inputFilename);
    std::ofstream outFile(outputFilename);

    if (!inFile.is_open()) {
        std::cerr << "Помилка: Не вдалося відкрити файл для читання " << inputFilename << std::endl;
        return;
    }
    if (!outFile.is_open()) {
        std::cerr << "Помилка: Не вдалося відкрити файл для запису " << outputFilename << std::endl;
        inFile.close(); // Закриваємо вхідний файл перед виходом
        return;
    }

    int number;
    // Зчитуємо число за числом безпосередньо з файлу (без масивів)
    while (inFile >> number) {
        if (isCosineValue(number)) {
            outFile << number << " ";
        }
    }

    inFile.close();
    outFile.close();
}


void displayFileContent(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Помилка: Не вдалося відкрити файл " << filename << std::endl;
        return;
    }

    int number;
    bool isEmpty = true;
    while (file >> number) {
        std::cout << number << " ";
        isEmpty = false;
    }

    if (isEmpty) {
        std::cout << "(Файл порожній)";
    }

    std::cout << std::endl;
    file.close();
}