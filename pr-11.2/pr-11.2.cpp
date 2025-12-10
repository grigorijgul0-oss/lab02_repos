#include <iostream>
#include <fstream>
#include <string>

// 1. Створення файлу t1 користувачем
void createTextFile(const std::string& fileName)
{
    std::ofstream fout(fileName);
    if (!fout.is_open()) {
        std::cout << "Cannot open file: " << fileName << std::endl;
        return;
    }

    std::cout << "File \"" << fileName << "\" created.\n";
    std::cout << "Enter text (empty line = finish):\n";

    std::string line;
    while (true) {
        std::getline(std::cin, line);
        if (line.empty()) break;
        fout << line << '\n';
    }

    std::cout << "Text saved.\n";
}

// 2. Читання файлу у рядок
bool readFile(const std::string& fileName, std::string& content)
{
    std::ifstream fin(fileName);
    if (!fin.is_open()) {
        std::cout << "Cannot open file: " << fileName << std::endl;
        return false;
    }

    content.assign(std::istreambuf_iterator<char>(fin),
                   std::istreambuf_iterator<char>());
    return true;
}

// 3. Нормалізація пробілів
std::string normalizeSpaces(const std::string& text)
{
    std::string result;
    result.reserve(text.size());

    std::size_t i = 0;
    std::size_t n = text.size();

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

    return result;
}

// 4. Запис у t2
bool writeFile(const std::string& fileName, const std::string& content)
{
    std::ofstream fout(fileName);
    if (!fout.is_open()) {
        std::cout << "Cannot open file: " << fileName << std::endl;
        return false;
    }

    fout << content;
    return true;
}

// 5. Вивід на екран вмісту файлу
void printFileOnScreen(const std::string& fileName)
{
    std::ifstream fin(fileName);
    if (!fin.is_open()) {
        std::cout << "Cannot open file: " << fileName << std::endl;
        return;
    }

    std::cout << "\n===== Content of " << fileName << " =====\n";

    std::string line;
    while (std::getline(fin, line)) {
        std::cout << line << '\n';
    }

    std::cout << "=====================================\n";
}

int main()
{
    std::string t1 = "t1.txt";
    std::string t2 = "t2.txt";

    // 1. Створюємо t1
    createTextFile(t1);

    // 2. Читаємо t1
    std::string original;
    if (!readFile(t1, original)) return 0;

    // 3. Нормалізуємо пробіли
    std::string normalized = normalizeSpaces(original);

    // 4. Записуємо у t2
    if (!writeFile(t2, normalized)) return 0;

    // 5. Виводимо t2 на екран
    printFileOnScreen(t2);

    return 0;
}
