#include "../include/Menu.h"
#include "../include/Shkolnik.h"
#include "../include/Ring.h"
#include "../include/InputUtils.h"

#include <iostream>
#include <iomanip>
#include <limits>
#include <cstring>
#include <cctype>

using std::cin;
using std::cout;
using std::setw;
using std::setfill;
using std::numeric_limits;
using std::streamsize;


static void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Проверка: содержит ли строка a подстроку b (без учета регистра).
// Нужна для поиска школьника по части фамилии.
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

// Локальное сравнение строк без учета регистра.
// Возвращает:
//   <0 если a < b; 0 если a == b; >0 если a > b (лексикографически)
// Используется при сортировке кольца по имени.
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
    // Если одна строка закончилась
    return static_cast<unsigned char>(*a) - static_cast<unsigned char>(*b);
}

// Отрисовка основного текстового меню.
// Здесь только "красота": рамка, выравнивание по ширине и список доступных действий.
static void printMenu() {
    const int width = 60;
    cout << "\n " << setfill('=') << setw(width) << "=" << setfill(' ') << '\n';
    std::string title = "СИСТЕМА УПРАВЛЕНИЯ ШКОЛЬНИКАМИ С КОЛЬЦОМ";
    int padding = (width - 2 - (int)title.length()) / 2;
    cout << " |" << setw(padding) << " " << title
         << setw(width - 2 - padding - (int)title.length()) << " " << '\n';
    cout << " " << setfill('=') << setw(width) << "=" << setfill(' ') << '\n';
    cout << " |  1. Добавить школьника в кольцо" << setw(width - 34) << " " << '\n';
    cout << " |  2. Показать всех из кольца" << setw(width - 28) << " " << '\n';
    cout << " |  3. Удалить школьника из кольца" << setw(width - 31) << " " << '\n';
    cout << " |  4. Найти школьника в кольце" << setw(width - 30) << " " << '\n';
    cout << " |  5. Отсортировать кольцо" << setw(width - 26) << " " << '\n';
    cout << " |  6. Показать размер кольца" << setw(width - 27) << " " << '\n';
    cout << " |  0. Выход" << setw(width - 13) << " " << '\n';
    cout << " " << setfill('=') << setw(width) << "=" << setfill(' ') << '\n';
    cout << " Выберите опцию: ";
}

// Основной цикл работы программы: вывод меню, чтение выбора, вызов операций над кольцом.
void Menu::run() {
    Ring<Shkolnik> ring;  // Кольцо для хранения школьников
    int choice;

    do {
        printMenu();
        // Безопасный ввод пункта меню с обработкой исключений
        choice = readInt(cin, "Ваш выбор: ", 0, 6);

        switch (choice) {
            case 1: {
                // Добавить школьника: считываем данные через перегруженный оператор >>
                Shkolnik newObject;
                cout << "Введите данные школьника:\n";
                cin >> newObject;
                clearInput(); // после ввода чисел подчистим хвост
                ring.add(newObject);
                cout << "Школьник добавлен в кольцо успешно!\n";
                break;
            }
            case 2: {
                // Показать всех: печатаем всю таблицу из кольца
                cout << "\n" << setfill('=') << setw(60) << "=" << setfill(' ') << '\n';
                cout << "                 ШКОЛЬНИКИ В КОЛЬЦЕ\n";
                cout << setfill('=') << setw(60) << "=" << setfill(' ') << '\n';
                if (!ring.isEmpty()) {
                    ring.display();
                } else {
                    cout << "Кольцо пусто.\n";
                    cout << setfill('=') << setw(60) << "=" << setfill(' ') << '\n';
                }
                break;
            }
            case 3: {
                // Удалить школьника: просим ввести ключевые поля и удаляем первое точное совпадение
                if (ring.isEmpty()) {
                    cout << "Кольцо пусто. Нечего удалять.\n";
                    break;
                }

                Shkolnik searchObj;
                cout << "Введите данные школьника для удаления:\n";
                char name[32];
                readName(cin, name, 32,
                         "Введите фамилию школьника (для удаления): ",
                         false);
                searchObj.setName(name);
                int age = readInt(cin, "Введите возраст школьника: ", 1, 120);
                searchObj.setAge(age);
                int grade = readInt(cin, "Введите класс школьника (1..11): ", 1, 11);
                searchObj.setGrade(grade);

                if (ring.remove(searchObj)) {
                    cout << "Школьник удален из кольца успешно!\n";
                } else {
                    cout << "Школьник не найден в кольце.\n";
                }
                break;
            }
            case 4: {
                // Расширенный поиск школьников:
                //  - по имени (подстрока, без учета регистра)
                //  - по возрасту (диапазон)
                //  - по классу (диапазон)
                //  - точное совпадение (имя, возраст, класс)
                if (ring.isEmpty()) {
                    cout << "Кольцо пусто. Нечего искать.\n";
                    break;
                }

                cout << "\nВыберите тип поиска:\n";
                cout << "  1. По имени (содержит, без учета регистра)\n";
                cout << "  2. По возрасту (диапазон)\n";
                cout << "  3. По классу (диапазон)\n";
                cout << "  4. Точное совпадение (имя, возраст, класс)\n";
                int sChoice = readInt(cin, "Ваш выбор: ", 1, 4);

                if (sChoice == 1) {
                    char query[32];
                    readName(cin, query, 32,
                             "Введите часть имени (для поиска): ",
                             false);
                    auto results = ring.findAll([&](const Shkolnik& s) {
                        return containsIgnoreCase(s.getName(), query);
                    });
                    // Вывод результатов в виде таблицы
                    if (results.empty()) {
                        cout << "Ничего не найдено.\n";
                    } else {
                        cout << "\nНайдено: " << results.size() << "\n";
                        results.front().printHeader();
                        cout << " " << setfill('=') << setw(60) << "=" << setfill(' ') << '\n';
                        for (const auto& it : results) {
                            it.printTable();
                        }
                        cout << " " << setfill('=') << setw(60) << "=" << setfill(' ') << '\n';
                    }
                } else if (sChoice == 2) {
                    int fromA = readInt(cin, "Введите возраст от: ", 1, 120);
                    int toA   = readInt(cin, "Введите возраст до: ", 1, 120);
                    if (fromA > toA) std::swap(fromA, toA);
                    auto results = ring.findAll([&](const Shkolnik& s) {
                        return s.getAge() >= fromA && s.getAge() <= toA;
                    });
                    // Вывод результатов в виде таблицы
                    if (results.empty()) {
                        cout << "Ничего не найдено.\n";
                    } else {
                        cout << "\nНайдено: " << results.size() << "\n";
                        results.front().printHeader();
                        cout << " " << setfill('=') << setw(60) << "=" << setfill(' ') << '\n';
                        for (const auto& it : results) {
                            it.printTable();
                        }
                        cout << " " << setfill('=') << setw(60) << "=" << setfill(' ') << '\n';
                    }
                } else if (sChoice == 3) {
                    int fromG = readInt(cin, "Введите класс от: ", 1, 11);
                    int toG   = readInt(cin, "Введите класс до: ", 1, 11);
                    if (fromG > toG) std::swap(fromG, toG);
                    auto results = ring.findAll([&](const Shkolnik& s) {
                        return s.getGrade() >= fromG && s.getGrade() <= toG;
                    });
                    // Вывод результатов в виде таблицы
                    if (results.empty()) {
                        cout << "Ничего не найдено.\n";
                    } else {
                        cout << "\nНайдено: " << results.size() << "\n";
                        results.front().printHeader();
                        cout << " " << setfill('=') << setw(60) << "=" << setfill(' ') << '\n';
                        for (const auto& it : results) {
                            it.printTable();
                        }
                        cout << " " << setfill('=') << setw(60) << "=" << setfill(' ') << '\n';
                    }
                } else if (sChoice == 4) {
                    Shkolnik searchObj;
                    char name[32];
                    readName(cin, name, 32,
                             "Введите фамилию (для точного поиска): ",
                             false);
                    searchObj.setName(name);
                    int age = readInt(cin, "Введите возраст: ", 1, 120);
                    searchObj.setAge(age);
                    int grade = readInt(cin, "Введите класс (1..11): ", 1, 11);
                    searchObj.setGrade(grade);
                    auto found = ring.search(searchObj);
                    if (found != nullptr) {
                        cout << "\nШкольник найден в кольце:\n";
                        cout << setfill('=') << setw(60) << "=" << setfill(' ') << '\n';
                        found->data.printHeader();
                        cout << " " << setfill('=') << setw(60) << "=" << setfill(' ') << '\n';
                        found->data.printTable();
                        cout << " " << setfill('=') << setw(60) << "=" << setfill(' ') << '\n';
                    } else {
                        cout << "Школьник не найден в кольце.\n";
                    }
                } else {
                    cout << "Неверный выбор типа поиска.\n";
                }
                break;
            }
            case 5: {
                // Расширенная сортировка кольца: по имени/возрасту/классу, по возрастанию или убыванию
                if (ring.isEmpty()) {
                    cout << "Кольцо пусто. Нечего сортировать.\n";
                    break;
                }
                cout << "\nВыберите поле сортировки:\n";
                cout << "  1. Имя\n";
                cout << "  2. Возраст\n";
                cout << "  3. Класс\n";
                int f = readInt(cin, "Ваш выбор: ", 1, 3);
                int o = readInt(cin, "Порядок: 1. По возрастанию  2. По убыванию: ", 1, 2);
                bool asc = (o != 2);
                if (f == 1) {
                    ring.sortWith([&](const Shkolnik& a, const Shkolnik& b){
                        const char* na = a.getName(); const char* nb = b.getName();
                        if (na == nullptr) na = "";
                        if (nb == nullptr) nb = "";
                        int cmp = compareIgnoreCase(na, nb);
                        return asc ? (cmp < 0) : (cmp > 0);
                    });
                } else if (f == 2) {
                    ring.sortWith([&](const Shkolnik& a, const Shkolnik& b){
                        return asc ? (a.getAge() < b.getAge()) : (a.getAge() > b.getAge());
                    });
                } else if (f == 3) {
                    ring.sortWith([&](const Shkolnik& a, const Shkolnik& b){
                        return asc ? (a.getGrade() < b.getGrade()) : (a.getGrade() > b.getGrade());
                    });
                } else {
                    cout << "Неверный выбор поля. Выполняется сортировка по имени (по умолчанию)...\n";
                    ring.sort();
                }
                cout << "Кольцо отсортировано!\n";
                break;
            }
            case 6: {
                // Показать размер кольца
                cout << "Размер кольца: " << ring.getSize() << " элементов.\n";
                break;
            }
            case 0: {
                cout << "До свидания!\n";
                break;
            }
            default: {
                cout << "Неверная опция!\n";
                break;
            }
        }

        if (choice != 0) {
            cout << "\nНажмите Enter для продолжения...";
            clearInput();
        }
    } while (choice != 0);
}
