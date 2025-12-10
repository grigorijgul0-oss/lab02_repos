#include <iostream>
#include <fstream>
#include <string>

// Функція створює текстовий файл з заданим ім'ям.
// Увесь текст користувач вводить з клавіатури.
// Порожній рядок означає кінець введення.
void createTextFile(const std::string& fileName)
{
    std::ofstream fout(fileName);
    if (!fout.is_open()) {
        std::cout << "Cannot open file: " << fileName << std::endl;
        return;
    }

    std::cout << "File \"" << fileName << "\" created." << std::endl;
    std::cout << "Enter text\n";

    std::string line;

    // Перед першим getline варто очистити буфер, якщо до цього вже було введення через >>
    // але тут ми одразу починаємо з getline, тому додатково нічого не потрібно.

    while (true) {
        std::getline(std::cin, line);
        if (line.empty()) {
            break; // кінець введення
        }
        fout << line << '\n';
    }

    std::cout << "Text saved." << std::endl;
}

// Функція обчислює кількість входжень послідовності ",-"
// у текстовому файлі з заданим ім'ям і повертає це число.
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
            // Якщо у файлі звичайний дефіс "-", так і залишаємо:
            if (line[j] == ',' && line[j + 1] == '-') {
                ++count;
            }

            
        }
    }

    return count;
}

// Функція виводить результат (щоб main був максимально простим).
void printResult(int count)
{
    std::cout << "count \",-\" in file: "
        << count << std::endl;
}

int main()
{
    std::string fileName = "t.txt";

    // 1. Створюємо файл і записуємо в нього текст
    createTextFile(fileName);

    // 2. Обчислюємо кількість пар ",-"
    int result = countCommaDash(fileName);

    // 3. Виводимо результат
    printResult(result);

    return 0;
}
