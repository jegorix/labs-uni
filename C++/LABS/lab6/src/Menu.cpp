#include "../include/Menu.h"
#include "../include/models/Shkolnik.h"
#include "../include/models/Student.h"
#include "../include/models/Uchaschiysya.h"
#include "../include/containers/Ring.h"
#include "../include/utils/InputUtils.h"
#include "../include/files/TextFile.h"
#include "../include/files/BinaryFile.h"
#include "../include/Exceptions.h"

#include <iostream>
#include <iomanip>
#include <limits>
#include <cstring>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>

using std::cin;
using std::cout;
using std::setw;
using std::setfill;
using std::numeric_limits;
using std::streamsize;
using std::string;
using std::vector;


static void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Объявления структур ниже по файлу
struct EntityStrings;
template<typename T> struct EntityTraits;

// Подсчёт длины UTF-8 строки в символах (по ведущим байтам).
static std::size_t utf8Len(const std::string& s) {
    std::size_t count = 0;
    for (unsigned char c : s) {
        if ((c & 0xC0) != 0x80) ++count;
    }
    return count;
}

static std::string padToWidth(const std::string& s, std::size_t width) {
    std::size_t len = utf8Len(s);
    if (len >= width) return s;
    return s + std::string(width - len, ' ');
}

// Проверка: содержит ли строка a подстроку b (без учета регистра).
// Нужна для поиска по части ФИО.
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

// Описание текстов и диапазонов для разных типов сущностей.
struct EntityStrings {
    std::string title;      // Заголовок меню
    std::string single;     // Имя сущности (винительный падеж) — "школьника"/"студента"
    std::string extraLabel; // Доп. поле — "класс"/"курс"
    int extraMin;
    int extraMax;
};

template<typename T>
struct EntityTraits;

template<>
struct EntityTraits<Shkolnik> {
    static EntityStrings strings() {
        return {
            "СИСТЕМА УПРАВЛЕНИЯ ШКОЛЬНИКАМИ С КОЛЬЦОМ",
            "школьника",
            "класс",
            1, 11
        };
    }
    static int getExtra(const Shkolnik& s) { return s.getGrade(); }
    static void setExtra(Shkolnik& s, int v) { s.setGrade(v); }
};

template<>
struct EntityTraits<Student> {
    static EntityStrings strings() {
        return {
            "СИСТЕМА УПРАВЛЕНИЯ СТУДЕНТАМИ С КОЛЬЦОМ",
            "студента",
            "курс",
            1, 6
        };
    }
    static int getExtra(const Student& s) { return s.getCourse(); }
    static void setExtra(Student& s, int v) { s.setCourse(v); }
};

// Построить таблицу с автошириной колонок по текущим данным.
template<typename T>
static void printTableData(const std::vector<T>& data, const EntityStrings& info) {
    if (data.empty()) {
        cout << "Кольцо пусто.\n";
        return;
    }

    auto strlenSafe = [](const char* s) -> std::size_t {
        return s ? utf8Len(s) : 0;
    };

    std::size_t nameW = std::max<std::size_t>(utf8Len("ФИО"), 3);
    std::size_t ageW = std::max<std::size_t>(utf8Len("Возраст"), 7);
    std::size_t extraW = std::max<std::size_t>(utf8Len(info.extraLabel), 5);

    for (const auto& item : data) {
        nameW = std::max(nameW, strlenSafe(item.getName()));
        ageW = std::max<std::size_t>(ageW, utf8Len(std::to_string(item.getAge())));
        extraW = std::max<std::size_t>(extraW, utf8Len(std::to_string(EntityTraits<T>::getExtra(item))));
    }

    std::size_t lineLen = nameW + ageW + extraW + 10; // разделители и пробелы
    auto printLine = [&]() { cout << std::string(lineLen, '=') << '\n'; };

    printLine();
    cout << "| " << padToWidth("ФИО", nameW)
         << " | " << padToWidth("Возраст", ageW)
         << " | " << padToWidth(info.extraLabel, extraW)
         << " |" << '\n';
    printLine();
    for (const auto& item : data) {
        const char* nm = item.getName();
        std::string ageStr = std::to_string(item.getAge());
        std::string extraStr = std::to_string(EntityTraits<T>::getExtra(item));
        cout << "| " << padToWidth(nm ? nm : "", nameW)
             << " | " << padToWidth(ageStr, ageW)
             << " | " << padToWidth(extraStr, extraW)
             << " |" << '\n';
    }
    printLine();
}

// Отрисовка основного текстового меню для выбранного типа сущности.
static void printMenu(const EntityStrings& info) {
    const int width = 60;
    cout << "\n " << setfill('=') << setw(width) << "=" << setfill(' ') << '\n';
    std::string title = info.title;
    int padding = (width - 2 - (int)title.length()) / 2;
    cout << " |" << setw(padding) << " " << title
         << setw(width - 2 - padding - (int)title.length()) << " " << '\n';
    cout << " " << setfill('=') << setw(width) << "=" << setfill(' ') << '\n';
    auto line = [&](const std::string& text) {
        cout << " |  " << text;
        int spaces = width - 4 - static_cast<int>(text.length());
        if (spaces < 0) spaces = 0;
        cout << setw(spaces) << " " << '\n';
    };
    line("1. Добавить " + info.single + " в кольцо");
    line("2. Показать всех из кольца");
    line("3. Удалить " + info.single + " из кольца");
    line("4. Найти " + info.single + " в кольце");
    line("5. Отсортировать кольцо");
    line("6. Показать размер кольца");
    line("7. Записать кольцо в текстовый файл");
    line("8. Прочитать кольцо из текстового файла");
    line("9. Записать кольцо в бинарный файл");
    line("10. Прочитать кольцо из бинарного файла");
    line("0. Выход");
    cout << " " << setfill('=') << setw(width) << "=" << setfill(' ') << '\n';
}

template<typename T>
static void runForEntity(const EntityStrings& info) {
    Ring<T> ring;
    int choice;

    auto askFileName = [](const std::string& prompt, const std::string& fallback) {
        cout << prompt;
        std::string name;
        std::getline(cin, name);
        if (name.empty()) return fallback;
        return name;
    };
    auto ensureDir = [](const std::string& path) {
        std::filesystem::path p(path);
        if (p.has_parent_path()) {
            std::filesystem::create_directories(p.parent_path());
        }
    };

    cout << "\nВыберите язык для ФИО:\n";
    cout << "  1. Русский (кириллица)\n";
    cout << "  2. Английский (латиница)\n";
    int lang = readInt(cin, "Ваш выбор: ", 1, 2);
    setUseRussianNames(lang == 1);

    do {
        printMenu(info);
        choice = readInt(cin, "Ваш выбор: ", 0, 10);

        switch (choice) {
            case 1: {
                T newObject;
                cout << "\nДобавление " << info.single << ":\n";
                cin >> newObject;
                clearInput();
                ring.add(newObject);
                cout << "Объект добавлен в кольцо успешно!\n";
                break;
            }
            case 2: {
                cout << "\n";
                auto all = ring.findAll([](const T&){ return true; });
                printTableData(all, info);
                break;
            }
            case 3: {
                if (ring.isEmpty()) {
                    cout << "Кольцо пусто. Нечего удалять.\n";
                    break;
                }

                std::string nameHint = useRussianNames() ? " (кириллица)" : " (латиница)";
                char query[Uchaschiysya::NAME_CAP];
                readName(cin, query, Uchaschiysya::NAME_CAP,
                         std::string("Введите фрагмент ФИО") + nameHint + " (для удаления): ",
                         useRussianNames());
                auto matches = ring.findAll([&](const T& s) {
                    return containsIgnoreCase(s.getName(), query);
                });
                if (matches.empty()) {
                    cout << "Элемент с таким ФИО не найден.\n";
                    break;
                }
                T target = matches.front();
                if (ring.remove(target)) {
                    cout << "Удаление выполнено успешно!\n";
                } else {
                    cout << "Элемент не найден в кольце.\n";
                }
                break;
            }
            case 4: {
                if (ring.isEmpty()) {
                    cout << "Кольцо пусто. Нечего искать.\n";
                    break;
                }

                cout << "\nВыберите тип поиска:\n";
                cout << "  1. По ФИО (содержит, без учета регистра)\n";
                cout << "  2. По возрасту (диапазон)\n";
                cout << "  3. По " << info.extraLabel << " (диапазон)\n";
                cout << "  4. Точное совпадение (ФИО, возраст, " << info.extraLabel << ")\n";
                int sChoice = readInt(cin, "Ваш выбор: ", 1, 4);

                if (sChoice == 1) {
                    std::string nameHint = useRussianNames() ? " (кириллица)" : " (латиница)";
                    std::string query;
                    while (true) {
                        cout << "Введите фрагмент ФИО" << nameHint << ": ";
                        std::getline(cin, query);
                        if (!query.empty()) break;
                        cout << "Фрагмент не может быть пустым. Повторите ввод.\n";
                    }
                    auto results = ring.findAll([&](const T& s) {
                        return containsIgnoreCase(s.getName(), query.c_str());
                    });
                    if (results.empty()) {
                        cout << "Ничего не найдено.\n";
                    } else {
                        cout << "\nНайдено: " << results.size() << "\n";
                        printTableData(results, info);
                    }
                } else if (sChoice == 2) {
                    int fromA = readInt(cin, "Введите возраст от: ", 1, 120);
                    int toA   = readInt(cin, "Введите возраст до: ", 1, 120);
                    if (fromA > toA) std::swap(fromA, toA);
                    auto results = ring.findAll([&](const T& s) {
                        return s.getAge() >= fromA && s.getAge() <= toA;
                    });
                    if (results.empty()) {
                        cout << "Ничего не найдено.\n";
                    } else {
                        cout << "\nНайдено: " << results.size() << "\n";
                        printTableData(results, info);
                    }
                } else if (sChoice == 3) {
                    int fromG = readInt(cin, "Введите " + info.extraLabel + " от: ",
                                        info.extraMin, info.extraMax);
                    int toG   = readInt(cin, "Введите " + info.extraLabel + " до: ",
                                        info.extraMin, info.extraMax);
                    if (fromG > toG) std::swap(fromG, toG);
                    auto results = ring.findAll([&](const T& s) {
                        return EntityTraits<T>::getExtra(s) >= fromG &&
                               EntityTraits<T>::getExtra(s) <= toG;
                    });
                    if (results.empty()) {
                        cout << "Ничего не найдено.\n";
                    } else {
                        cout << "\nНайдено: " << results.size() << "\n";
                        printTableData(results, info);
                    }
                } else if (sChoice == 4) {
                    std::string nameHint = useRussianNames() ? " (кириллица)" : " (латиница)";
                    T searchObj;
                    char name[Uchaschiysya::NAME_CAP];
                    readName(cin, name, Uchaschiysya::NAME_CAP,
                             std::string("Введите ФИО") + nameHint + " (для точного поиска): ",
                             useRussianNames());
                    searchObj.setName(name);
                    int age = readInt(cin, "Введите возраст: ", 1, 120);
                    searchObj.setAge(age);
                    int extra = readInt(cin, "Введите " + info.extraLabel + " (" +
                                             std::to_string(info.extraMin) + ".." +
                                             std::to_string(info.extraMax) + "): ",
                                       info.extraMin, info.extraMax);
                    EntityTraits<T>::setExtra(searchObj, extra);
                    auto found = ring.search(searchObj);
                    if (found != nullptr) {
                        cout << "\nНайден элемент в кольце:\n";
                        printTableData(std::vector<T>{found->data}, info);
                    } else {
                        cout << "Ничего не найдено.\n";
                    }
                } else {
                    cout << "Неверный выбор типа поиска.\n";
                }
                break;
            }
            case 5: {
                if (ring.isEmpty()) {
                    cout << "Кольцо пусто. Нечего сортировать.\n";
                    break;
                }
                cout << "\nВыберите поле сортировки:\n";
                cout << "  1. ФИО\n";
                cout << "  2. Возраст\n";
                cout << "  3. " << info.extraLabel << "\n";
                int f = readInt(cin, "Ваш выбор: ", 1, 3);
                int o = readInt(cin, "Порядок: 1. По возрастанию  2. По убыванию: ", 1, 2);
                bool asc = (o != 2);
                if (f == 1) {
                    ring.sortWith([&](const T& a, const T& b){
                        const char* na = a.getName(); const char* nb = b.getName();
                        if (na == nullptr) na = "";
                        if (nb == nullptr) nb = "";
                        int cmp = compareIgnoreCase(na, nb);
                        return asc ? (cmp < 0) : (cmp > 0);
                    });
                } else if (f == 2) {
                    ring.sortWith([&](const T& a, const T& b){
                        return asc ? (a.getAge() < b.getAge()) : (a.getAge() > b.getAge());
                    });
                } else if (f == 3) {
                    ring.sortWith([&](const T& a, const T& b){
                        return asc ? (EntityTraits<T>::getExtra(a) < EntityTraits<T>::getExtra(b))
                                   : (EntityTraits<T>::getExtra(a) > EntityTraits<T>::getExtra(b));
                    });
                } else {
                    cout << "Неверный выбор поля. Выполняется сортировка по имени (по умолчанию)...\n";
                    ring.sort();
                }
                cout << "Кольцо отсортировано!\n";
                break;
            }
            case 6: {
                cout << "Размер кольца: " << ring.getSize() << " элементов.\n";
                break;
            }
            case 7: {
                if (ring.isEmpty()) {
                    cout << "Кольцо пусто. Нечего записывать.\n";
                    break;
                }
                std::string fname = askFileName("Введите имя текстового файла (по умолчанию text_file/ring.txt): ",
                                                "text_file/ring.txt");
                ensureDir(fname);
                TextFile<T> tf(fname);
                tf.clearFile();
                auto all = ring.findAll([](const T&){ return true; });
                for (const auto& item : all) {
                    tf.saveRecord(item);
                }
                cout << "Кольцо записано в текстовый файл.\n";
                break;
            }
            case 8: {
                std::string fname = askFileName("Введите имя текстового файла для чтения (по умолчанию text_file/ring.txt): ",
                                                "text_file/ring.txt");
                ensureDir(fname);
                TextFile<T> tf(fname);
                try {
                    auto items = tf.readAllRecords();
                    ring.clear();
                    for (const auto& it : items) {
                        ring.add(it);
                    }
                    cout << "Текстовый файл прочитан, элементы загружены в кольцо.\n";
                } catch (const Exception& ex) {
                    cout << "Ошибка файла: " << ex.what() << "\n";
                }
                break;
            }
            case 9: {
                if (ring.isEmpty()) {
                    cout << "Кольцо пусто. Нечего записывать.\n";
                    break;
                }
                std::string fname = askFileName("Введите имя бинарного файла (по умолчанию bin_file/ring.bin): ",
                                                "bin_file/ring.bin");
                ensureDir(fname);
                BinaryFile<T> bf(fname);
                bf.clearFile();
                auto all = ring.findAll([](const T&){ return true; });
                for (const auto& item : all) {
                    bf.saveRecord(item);
                }
                cout << "Кольцо записано в бинарный файл.\n";
                break;
            }
            case 10: {
                std::string fname = askFileName("Введите имя бинарного файла для чтения (по умолчанию bin_file/ring.bin): ",
                                                "bin_file/ring.bin");
                ensureDir(fname);
                BinaryFile<T> bf(fname);
                try {
                    auto items = bf.readAllRecords();
                    ring.clear();
                    for (const auto& it : items) {
                        ring.add(it);
                    }
                    cout << "Бинарный файл прочитан, элементы загружены в кольцо.\n";
                } catch (const Exception& ex) {
                    cout << "Ошибка файла: " << ex.what() << "\n";
                }
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

// Основной цикл: выбор типа сущности и запуск соответствующего меню.
void Menu::run() {
    cout << "Выберите тип объектов для работы:\n";
    cout << "  1. Школьники\n";
    cout << "  2. Студенты\n";
    int entityChoice = readInt(cin, "Ваш выбор: ", 1, 2);

    if (entityChoice == 2) {
        runForEntity<Student>(EntityTraits<Student>::strings());
    } else {
        runForEntity<Shkolnik>(EntityTraits<Shkolnik>::strings());
    }
}
