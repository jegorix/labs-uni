#include "../include/InputUtils.h"

#include <iostream>
#include <limits>
#include <cctype>

using std::cin;
using std::cout;
using std::string;
using std::numeric_limits;
using std::streamsize;

static void clearInput(std::istream& in) {
    in.clear();
    in.ignore(numeric_limits<streamsize>::max(), '\n');
}

static bool gRussianNames = false;

bool useRussianNames() {
    return gRussianNames;
}

void setUseRussianNames(bool russian) {
    gRussianNames = russian;
}

int readInt(std::istream& in,
            const std::string& prompt,
            int minValue,
            int maxValue) {
    while (true) {
        cout << prompt;
        string line;
        if (!std::getline(in, line)) {
            clearInput(in);
            continue;
        }
        if (line.empty()) {
            cout << "Пустой ввод. Введите число.\n";
            continue;
        }

        bool ok = true;
        std::size_t pos = 0;
        if (line[0] == '-' || line[0] == '+') pos = 1;
        for (; pos < line.size(); ++pos) {
            if (!std::isdigit(static_cast<unsigned char>(line[pos]))) {
                ok = false;
                break;
            }
        }
        if (!ok) {
            cout << "Ожидалось целое число. Повторите ввод.\n";
            continue;
        }

        int value = std::stoi(line);
        if (value < minValue || value > maxValue) {
            cout << "Число вне допустимого диапазона. Повторите ввод.\n";
            continue;
        }
        return value;
    }
}

// Простая проверка: только буквы (латиница/кириллица) плюс пробел/дефис.
static bool isLatinLetter(unsigned char ch) {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

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
        cout << prompt;
        string line;
        if (!std::getline(in, line)) {
            clearInput(in);
            continue;
        }
        if (line.empty()) {
            cout << "ФИО не может быть пустым. Повторите ввод.\n";
            continue;
        }
        if (line.size() >= bufferSize) {
            cout << "ФИО слишком длинное (максимум " << (bufferSize - 1) << " символов).\n";
            continue;
        }

        bool ok = true;
        for (char ch : line) {
            unsigned char uch = static_cast<unsigned char>(ch);
            if (ch == ' ' || ch == '-') continue;
            if (russianOnly) {
                if (!isRussianLike(uch)) { ok = false; break; }
            } else {
                if (!isLatinLetter(uch)) { ok = false; break; }
            }
        }
        if (!ok) {
            cout << "ФИО должно содержать только буквы выбранного языка и пробел/дефис.\n";
            continue;
        }

        std::strncpy(buffer, line.c_str(), bufferSize);
        buffer[bufferSize - 1] = '\0';
        return;
    }
}
