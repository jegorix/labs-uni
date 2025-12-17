//
// Лаба 5: набор функций для безопасного ввода и валидации данных с обработкой исключений.
//

#ifndef LAB4_INPUT_UTILS_H
#define LAB4_INPUT_UTILS_H

#include <cstddef>
#include <string>
#include <iosfwd>

enum class NameLanguage {
    Russian,
    English
};

class NameValidator {
public:
    explicit NameValidator(NameLanguage lang);
    // Возвращает нормализованную строку (обрезаны лишние пробелы, слова разделены одним пробелом).
    // Бросает InputException при ошибке.
    std::string normalize(const std::string& raw, std::size_t bufferSize) const;
private:
    NameLanguage lang_;
    bool isLetter(unsigned char ch) const;
    bool isUpper(unsigned char ch) const;
};

// Считать целое число с проверкой диапазона.
// Вместо прямого использования cin >> x вызываем эту функцию.
// Она сама обрабатывает ошибки, просит ввести значение повторно и
// возвращает корректное число.
int readInt(std::istream& in,
            const std::string& prompt,
            int minValue,
            int maxValue);

// Глобальная настройка: использовать кириллицу или латиницу при вводе ФИО.
bool useRussianNames();
void setUseRussianNames(bool russian);

// Считать строку с ФИО (одно поле) с валидацией.
// Можно ограничить только буквами, только латиницей/кириллицей и т.п.
void readName(std::istream& in,
              char* buffer,
              std::size_t bufferSize,
              const std::string& prompt,
              bool russianOnly);

#endif // LAB4_INPUT_UTILS_H
