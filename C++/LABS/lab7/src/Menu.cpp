#include "../include/Menu.h"
#include "../include/Shkolnik.h"
#include "../include/Ring.h"
#include "../include/InputUtils.h"
#include "../include/File.h"

#include <iostream>
#include <iomanip>
#include <limits>
#include <cstring>
#include <cctype>
#include <string>
#include <algorithm>

using std::cin;
using std::cout;
using std::setw;
using std::setfill;
using std::numeric_limits;
using std::streamsize;
using std::string;

static void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

static std::string askFileName(const std::string& prompt, const std::string& fallback) {
    cout << prompt;
    std::string name;
    std::getline(cin, name);
    if (name.empty()) return fallback;
    return name;
}

static bool containsIgnoreCase(const char* a, const char* b) {
    if (a == nullptr || b == nullptr) return false;
    size_t lenA = std::strlen(a);
    size_t lenB = std::strlen(b);
    if (lenB == 0) return true;
    if (lenB > lenA) return false;
    for (size_t i = 0; i + lenB <= lenA; ++i) {
        bool match = true;
        for (size_t j = 0; j < lenB; ++j) {
            unsigned char ca = static_cast<unsigned char>(a[i + j]);
            unsigned char cb = static_cast<unsigned char>(b[j]);
            if (std::tolower(ca) != std::tolower(cb)) {
                match = false;
                break;
            }
        }
        if (match) return true;
    }
    return false;
}

static int compareIgnoreCase(const char* a, const char* b) {
    if (a == nullptr && b == nullptr) return 0;
    if (a == nullptr) return -1;
    if (b == nullptr) return 1;
    while (*a && *b) {
        unsigned char ca = static_cast<unsigned char>(*a);
        unsigned char cb = static_cast<unsigned char>(*b);
        int da = std::tolower(ca);
        int db = std::tolower(cb);
        if (da != db) return da - db;
        ++a; ++b;
    }
    return static_cast<unsigned char>(*a) - static_cast<unsigned char>(*b);
}

static void printMenu() {
    const int width = 72;
    cout << "\n " << setfill('=') << setw(width) << "=" << setfill(' ') << '\n';
    std::string title = "СИСТЕМА УПРАВЛЕНИЯ ШКОЛЬНИКАМИ (Кольцо)";
    int padding = (width - 2 - (int)title.length()) / 2;
    cout << " |" << setw(padding) << " " << title
         << setw(width - 2 - padding - (int)title.length()) << " " << "\n";
    cout << " " << setfill('=') << setw(width) << "=" << setfill(' ') << '\n';
    cout << " |  1. Добавить школьника в кольцо" << setw(width - 34) << " " << "\n";
    cout << " |  2. Показать всех из кольца" << setw(width - 28) << " " << "\n";
    cout << " |  3. Удалить школьника из кольца" << setw(width - 31) << " " << "\n";
    cout << " |  4. Найти школьника в кольце" << setw(width - 30) << " " << "\n";
    cout << " |  5. Отсортировать копию кольца" << setw(width - 34) << " " << "\n";
    cout << " |  6. Показать размер кольца" << setw(width - 29) << " " << "\n";
    cout << " |  7. Записать кольцо в текстовый файл" << setw(width - 42) << " " << "\n";
    cout << " |  8. Прочитать кольцо из текстового файла" << setw(width - 45) << " " << "\n";
    cout << " |  9. Записать кольцо в бинарный файл" << setw(width - 42) << " " << "\n";
    cout << " | 10. Прочитать кольцо из бинарного файла" << setw(width - 45) << " " << "\n";
    cout << " |  0. Выход" << setw(width - 13) << " " << "\n";
    cout << " " << setfill('=') << setw(width) << "=" << setfill(' ') << '\n';
    cout << " Выберите опцию: ";
}

void Menu::run() {
    Ring queue;
    int choice;

    do {
        printMenu();
        choice = readInt(cin, "Ваш выбор: ", 0, 10);

        switch (choice) {
            case 1: {
                Shkolnik obj;
                cout << "Введите данные школьника:\n";
                cin >> obj;
                clearInput();
                queue.add(obj);
                cout << "Школьник добавлен в кольцо успешно!\n";
                break;
            }
            case 2: {
                cout << "\n" << setfill('=') << setw(60) << "=" << setfill(' ') << '\n';
                cout << "              ШКОЛЬНИКИ В КОЛЬЦЕ\n";
                cout << setfill('=') << setw(60) << "=" << setfill(' ') << '\n';
                if (!queue.isEmpty()) {
                    queue.display();
                } else {
                    cout << "Кольцо пусто.\n";
                    cout << setfill('=') << setw(60) << "=" << setfill(' ') << '\n';
                }
                break;
            }
            case 3: {
                if (queue.isEmpty()) {
                    cout << "Кольцо пусто. Нечего удалять.\n";
                    break;
                }
                Shkolnik key;
                char name[32];
                readName(cin, name, 32, "Введите фамилию (для удаления): ", false);
                key.setName(name);
                key.setAge(readInt(cin, "Введите возраст: ", 1, 120));
                key.setGrade(readInt(cin, "Введите класс (1..11): ", 1, 11));
                if (queue.remove(key)) {
                    cout << "Школьник удален.\n";
                } else {
                    cout << "Не найден.\n";
                }
                break;
            }
            case 4: {
                if (queue.isEmpty()) {
                    cout << "Кольцо пусто. Нечего искать.\n";
                    break;
                }
                cout << "\nВыберите тип поиска:\n";
                cout << "  1. По имени (подстрока)\n";
                cout << "  2. По возрасту (диапазон)\n";
                cout << "  3. По классу (диапазон)\n";
                cout << "  4. Точное совпадение\n";
                int sel = readInt(cin, "Ваш выбор: ", 1, 4);
                if (sel == 1) {
                    char query[32];
                    readName(cin, query, 32, "Введите часть имени: ", false);
                    auto res = queue.findAll([&](const Shkolnik& s){ return containsIgnoreCase(s.getName(), query); });
                    if (res.empty()) cout << "Ничего не найдено.\n";
                    else {
                        res.front().printHeader();
                        cout << " " << setfill('=') << setw(60) << "=" << setfill(' ') << '\n';
                        for (auto& s : res) s.printTable();
                        cout << " " << setfill('=') << setw(60) << "=" << setfill(' ') << '\n';
                    }
                } else if (sel == 2) {
                    int a = readInt(cin, "Возраст от: ", 1, 120);
                    int b = readInt(cin, "Возраст до: ", 1, 120);
                    if (a > b) std::swap(a, b);
                    auto res = queue.findAll([&](const Shkolnik& s){ return s.getAge() >= a && s.getAge() <= b; });
                    if (res.empty()) cout << "Ничего не найдено.\n";
                    else {
                        res.front().printHeader();
                        cout << " " << setfill('=') << setw(60) << "=" << setfill(' ') << '\n';
                        for (auto& s : res) s.printTable();
                        cout << " " << setfill('=') << setw(60) << "=" << setfill(' ') << '\n';
                    }
                } else if (sel == 3) {
                    int a = readInt(cin, "Класс от: ", 1, 11);
                    int b = readInt(cin, "Класс до: ", 1, 11);
                    if (a > b) std::swap(a, b);
                    auto res = queue.findAll([&](const Shkolnik& s){ return s.getGrade() >= a && s.getGrade() <= b; });
                    if (res.empty()) cout << "Ничего не найдено.\n";
                    else {
                        res.front().printHeader();
                        cout << " " << setfill('=') << setw(60) << "=" << setfill(' ') << '\n';
                        for (auto& s : res) s.printTable();
                        cout << " " << setfill('=') << setw(60) << "=" << setfill(' ') << '\n';
                    }
                } else {
                    Shkolnik key;
                    char name[32];
                    readName(cin, name, 32, "Введите фамилию: ", false);
                    key.setName(name);
                    key.setAge(readInt(cin, "Введите возраст: ", 1, 120));
                    key.setGrade(readInt(cin, "Введите класс (1..11): ", 1, 11));
                    auto res = queue.findAll([&](const Shkolnik& s){ return s == key; });
                    if (res.empty()) cout << "Ничего не найдено.\n";
                    else {
                        res.front().printHeader();
                        cout << " " << setfill('=') << setw(60) << "=" << setfill(' ') << '\n';
                        res.front().printTable();
                        cout << " " << setfill('=') << setw(60) << "=" << setfill(' ') << '\n';
                    }
                }
                break;
            }
            case 5: {
                if (queue.isEmpty()) {
                    cout << "Кольцо пусто. Нечего сортировать.\n";
                    break;
                }
                cout << "\nПоле сортировки:\n  1. Имя\n  2. Возраст\n  3. Класс\n";
                int f = readInt(cin, "Ваш выбор: ", 1, 3);
                bool asc = readInt(cin, "Порядок (1-возр, 2-убыв): ", 1, 2) == 1;
                auto data = queue.toVector();
                if (f == 1) {
                    std::sort(data.begin(), data.end(), [&](const Shkolnik& a, const Shkolnik& b){
                        const char* na = a.getName(); const char* nb = b.getName();
                        if (na == nullptr) na = ""; if (nb == nullptr) nb = "";
                        int cmp = compareIgnoreCase(na, nb);
                        return asc ? (cmp < 0) : (cmp > 0);
                    });
                } else if (f == 2) {
                    std::sort(data.begin(), data.end(), [&](const Shkolnik& a, const Shkolnik& b){
                        return asc ? (a.getAge() < b.getAge()) : (a.getAge() > b.getAge());
                    });
                } else {
                    std::sort(data.begin(), data.end(), [&](const Shkolnik& a, const Shkolnik& b){
                        return asc ? (a.getGrade() < b.getGrade()) : (a.getGrade() > b.getGrade());
                    });
                }
                cout << "Отсортированное представление:\n";
                data.front().printHeader();
                cout << " " << setfill('=') << setw(60) << "=" << setfill(' ') << '\n';
                for (auto& s : data) s.printTable();
                cout << " " << setfill('=') << setw(60) << "=" << setfill(' ') << '\n';
                break;
            }
            case 6: {
                cout << "Размер кольца: " << queue.getSize() << " элементов.\n";
                break;
            }
            case 7: {
                if (queue.isEmpty()) {
                    cout << "Кольцо пусто. Нечего записывать.\n";
                    break;
                }
                string fileName = askFileName("Имя текстового файла (по умолчанию shkolniki.txt): ", "shkolniki.txt");
                try {
                    TextFile<Shkolnik> textFile(fileName);
                    textFile.write(queue.toVector());
                    cout << "Кольцо записано в текстовый файл \"" << fileName << "\".\n";
                } catch (const FileException& e) {
                    cout << "Ошибка файла: " << e.what() << "\n";
                }
                break;
            }
            case 8: {
                string fileName = askFileName("Имя текстового файла для чтения: ", "shkolniki.txt");
                int before = queue.getSize();
                try {
                    TextFile<Shkolnik> textFile(fileName);
                    auto items = textFile.read();
                    for (auto& i : items) queue.add(i);
                    cout << "Из файла добавлено " << (queue.getSize() - before) << " записей.\n";
                } catch (const FileException& e) {
                    cout << "Ошибка файла: " << e.what() << "\n";
                }
                break;
            }
            case 9: {
                if (queue.isEmpty()) {
                    cout << "Кольцо пусто. Нечего записывать.\n";
                    break;
                }
                string fileName = askFileName("Имя бинарного файла (по умолчанию shkolniki.bin): ", "shkolniki.bin");
                try {
                    BinaryFile<Shkolnik> binFile(fileName);
                    binFile.write(queue.toVector());
                    cout << "Кольцо записано в бинарный файл \"" << fileName << "\".\n";
                } catch (const FileException& e) {
                    cout << "Ошибка файла: " << e.what() << "\n";
                }
                break;
            }
            case 10: {
                string fileName = askFileName("Имя бинарного файла для чтения: ", "shkolniki.bin");
                int before = queue.getSize();
                try {
                    BinaryFile<Shkolnik> binFile(fileName);
                    auto items = binFile.read();
                    for (auto& i : items) queue.add(i);
                    cout << "Из бинарного файла добавлено " << (queue.getSize() - before) << " записей.\n";
                } catch (const FileException& e) {
                    cout << "Ошибка файла: " << e.what() << "\n";
                }
                break;
            }
            case 0: {
                cout << "До свидания!\n";
                break;
            }
            default: cout << "Неверная опция!\n"; break;
        }

        if (choice != 0) {
            cout << "\nНажмите Enter для продолжения...";
            clearInput();
        }
    } while (choice != 0);
}
