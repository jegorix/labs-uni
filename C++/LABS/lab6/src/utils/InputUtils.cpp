#include "../../include/utils/InputUtils.h"
#include "../../include/Exceptions.h"

#include <iostream>
#include <limits>
#include <cctype>
#include <sstream>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::numeric_limits;
using std::streamsize;

// Текущая настройка валидации ФИО: false — латиница, true — кириллица.
static bool gRussianNames = false;

bool useRussianNames() {
    return gRussianNames;
}

void setUseRussianNames(bool russian) {
    gRussianNames = russian;
}

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
static bool isLatinLetter(uint32_t ch) {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

static bool isLatinUpper(uint32_t ch) {
    return (ch >= 'A' && ch <= 'Z');
}

static bool isCyrillicLetter(uint32_t ch) {
    // Базовый диапазон кириллицы в Unicode
    return (ch >= 0x0400 && ch <= 0x04FF);
}

static bool isCyrillicUpper(uint32_t ch) {
    return (ch >= 0x0410 && ch <= 0x042F) || ch == 0x0401; // А-Я, Ё
}

// Простейший разбор UTF‑8 в кодпоинты. Бросаем InputException при ошибке.
static std::vector<uint32_t> decodeUtf8(const std::string& s) {
    std::vector<uint32_t> out;
    for (size_t i = 0; i < s.size();) {
        unsigned char c = static_cast<unsigned char>(s[i]);
        uint32_t cp = 0;
        size_t len = 0;
        if (c < 0x80) {
            cp = c;
            len = 1;
        } else if ((c >> 5) == 0x6) { // 110xxxxx
            if (i + 1 >= s.size()) throw InputException(16, "Некорректная UTF-8 последовательность в ФИО.");
            cp = (c & 0x1F) << 6;
            cp |= (static_cast<unsigned char>(s[i + 1]) & 0x3F);
            len = 2;
        } else if ((c >> 4) == 0xE) { // 1110xxxx
            if (i + 2 >= s.size()) throw InputException(16, "Некорректная UTF-8 последовательность в ФИО.");
            cp = (c & 0x0F) << 12;
            cp |= (static_cast<unsigned char>(s[i + 1]) & 0x3F) << 6;
            cp |= (static_cast<unsigned char>(s[i + 2]) & 0x3F);
            len = 3;
        } else {
            throw InputException(16, "Некорректная UTF-8 последовательность в ФИО.");
        }
        out.push_back(cp);
        i += len;
    }
    return out;
}

NameValidator::NameValidator(NameLanguage lang) : lang_(lang) {}

std::string NameValidator::normalize(const std::string& raw, std::size_t bufferSize) const {
    // Сжимаем пробелы и убираем лидирующие/замыкающие.
    std::string collapsed;
    bool inSpace = true;
    for (char ch : raw) {
        if (ch == ' ') {
            inSpace = true;
        } else {
            if (!collapsed.empty() && inSpace) collapsed.push_back(' ');
            collapsed.push_back(ch);
            inSpace = false;
        }
    }

    if (collapsed.empty()) {
        throw InputException(10, "ФИО не может быть пустым. Повторите ввод.");
    }
    if (collapsed.size() >= bufferSize) {
        throw InputException(11, "ФИО слишком длинное (максимум " +
                                   std::to_string(bufferSize - 1) + " символов). Повторите ввод.");
    }

    std::istringstream iss(collapsed);
    std::string word;
    std::string normalized;
    int parts = 0;
    while (iss >> word) {
        ++parts;
        if (parts > 3) break;
        if (!normalized.empty()) normalized.push_back(' ');
        if (word.empty()) continue;

        auto letters = decodeUtf8(word);

        // Проверим алфавит до проверки регистра
        auto isCorrectLetter = [&](uint32_t cp){
            return lang_ == NameLanguage::Russian ? isCyrillicLetter(cp) : isLatinLetter(cp);
        };
        auto isCorrectUpper = [&](uint32_t cp){
            return lang_ == NameLanguage::Russian ? isCyrillicUpper(cp) : isLatinUpper(cp);
        };

        bool lastHyphen = false;
        for (size_t i = 0; i < letters.size(); ++i) {
            uint32_t cp = letters[i];

            if (cp == '-') {
                if (i == 0 || i + 1 == letters.size() || lastHyphen) {
                    throw InputException(14, "Дефис в ФИО должен разделять части слова и не может стоять подряд.");
                }
                lastHyphen = true;
                continue;
            }
            lastHyphen = false;

            if (!isCorrectLetter(cp)) {
                throw InputException(15, "ФИО должно содержать только буквы выбранного языка и дефис.");
            }

            if (i == 0 && !isCorrectUpper(cp)) {
                throw InputException(13, "Каждое слово ФИО должно начинаться с заглавной буквы выбранного языка.");
            }
        }

        normalized += word;
    }

    if (parts != 3) {
        throw InputException(12, "ФИО должно состоять ровно из трех слов, разделённых пробелом.");
    }

    return normalized;
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

            NameValidator validator(russianOnly ? NameLanguage::Russian : NameLanguage::English);
            std::string normalized = validator.normalize(line, bufferSize);

            std::strncpy(buffer, normalized.c_str(), bufferSize);
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
