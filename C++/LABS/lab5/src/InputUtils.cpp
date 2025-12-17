#include "../include/InputUtils.h"
#include "../include/Exceptions.h"

#include <iostream>
#include <limits>
#include <cctype>

using std::cin;
using std::cout;
using std::string;
using std::numeric_limits;
using std::streamsize;

// Вспомогательная функция для очистки входного потока
static void clearInput(std::istream& in) {
    in.clear();
    in.ignore(numeric_limits<streamsize>::max(), '\n');
}

int readInt(std::istream& in,
            const std::string& prompt,
            int minValue,
            int maxValue) {
    while (true) {
        try {
            cout << prompt;
            string line;
            std::getline(in, line);

            if (line.empty()) {
                throw InputException(1, "Пустой ввод. Введите число.");
            }

            // Проверяем, что все символы - цифры (и, опционально, знак '-')
            std::size_t pos = 0;
            if (line[0] == '-' || line[0] == '+') {
                pos = 1;
            }
            for (; pos < line.size(); ++pos) {
                if (!std::isdigit(static_cast<unsigned char>(line[pos]))) {
                    throw InputException(2, "Ожидалось целое число. Повторите ввод.");
                }
            }

            int value = std::stoi(line);
            if (value < minValue || value > maxValue) {
                throw InputException(3, "Число вне допустимого диапазона. Повторите ввод.");
            }

            return value;
        } catch (const InputException& ex) {
            cout << "Ошибка ввода (" << ex.getCode() << "): " << ex.what() << "\n";
            clearInput(in);
        } catch (const std::exception& ex) {
            cout << "Неожиданная ошибка при вводе числа: " << ex.what() << "\nПовторите ввод.\n";
            clearInput(in);
        }
    }
}

// Проверка, что символ - буква латинского алфавита
static bool isLatinLetter(unsigned char ch) {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

// Простейшая проверка кириллицы в однобайтовой кодировке (в реальности под UTF‑8 нужна более
// сложная логика, но для учебной задачи ограничимся проверкой "не цифра и не пунктуация").
static bool isRussianLike(unsigned char ch) {
    if (std::isdigit(ch) || std::ispunct(ch)) return false;
    return true;
}

void readName(std::istream& in,
              char* buffer,
              std::size_t bufferSize,
              const std::string& prompt,
              bool russianOnly) {
    while (true) {
        try {
            cout << prompt;
            string line;
            std::getline(in, line);

            if (line.empty()) {
                throw InputException(10, "Имя не может быть пустым. Повторите ввод.");
            }
            if (line.size() >= bufferSize) {
                throw InputException(11, "Имя слишком длинное. Повторите ввод.");
            }

            for (char ch : line) {
                unsigned char uch = static_cast<unsigned char>(ch);
                if (ch == ' ' || ch == '-' ) continue; // разрешим пробел и дефис в фамилии

                if (russianOnly) {
                    if (!isRussianLike(uch)) {
                        throw InputException(12, "Ожидалась фамилия только на русском языке (буквы и пробел/дефис).");
                    }
                } else {
                    if (!isLatinLetter(uch)) {
                        throw InputException(13, "Ожидалась фамилия только латиницей (A-Z, a-z).");
                    }
                }
            }

            std::strncpy(buffer, line.c_str(), bufferSize);
            buffer[bufferSize - 1] = '\0';
            return;
        } catch (const InputException& ex) {
            cout << "Ошибка ввода (" << ex.getCode() << "): " << ex.what() << "\n";
            clearInput(in);
        } catch (const std::exception& ex) {
            cout << "Неожиданная ошибка при вводе имени: " << ex.what() << "\nПовторите ввод.\n";
            clearInput(in);
        }
    }
}

// Проверка корректности даты "dd.mm.yyyy"
static bool isValidDate(const string& s) {
    if (s.size() != 10) return false;
    if (s[2] != '.' || s[5] != '.') return false;
    for (std::size_t i = 0; i < s.size(); ++i) {
        if (i == 2 || i == 5) continue;
        if (!std::isdigit(static_cast<unsigned char>(s[i]))) return false;
    }
    int day = std::stoi(s.substr(0, 2));
    int mon = std::stoi(s.substr(3, 2));
    int year = std::stoi(s.substr(6, 4));
    if (year < 1900 || year > 2100) return false;
    if (mon < 1 || mon > 12) return false;
    int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    // Простейшая проверка високосного года
    bool leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    int dim = daysInMonth[mon - 1];
    if (mon == 2 && leap) dim = 29;
    if (day < 1 || day > dim) return false;
    return true;
}

std::string readDate(std::istream& in,
                     const std::string& prompt) {
    while (true) {
        try {
            cout << prompt << " (формат ДД.ММ.ГГГГ): ";
            string s;
            std::getline(in, s);

            if (!isValidDate(s)) {
                throw InputException(20, "Неверный формат или некорректная дата. Повторите ввод.");
            }

            return s;
        } catch (const InputException& ex) {
            cout << "Ошибка ввода (" << ex.getCode() << "): " << ex.what() << "\n";
            clearInput(in);
        } catch (const std::exception& ex) {
            cout << "Неожиданная ошибка при вводе даты: " << ex.what() << "\nПовторите ввод.\n";
            clearInput(in);
        }
    }
}


