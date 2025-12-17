//
// Лаба 5: набор функций для безопасного ввода и валидации данных с обработкой исключений.
//

#ifndef LAB4_INPUT_UTILS_H
#define LAB4_INPUT_UTILS_H

#include <string>
#include <iosfwd>

// Считать целое число с проверкой диапазона.
// Вместо прямого использования cin >> x вызываем эту функцию.
// Она сама обрабатывает ошибки, просит ввести значение повторно и
// возвращает корректное число.
int readInt(std::istream& in,
            const std::string& prompt,
            int minValue,
            int maxValue);

// Считать строку-имя (например, фамилию) с валидацией.
// Можно ограничить только буквами, только латиницей/кириллицей и т.п.
void readName(std::istream& in,
              char* buffer,
              std::size_t bufferSize,
              const std::string& prompt,
              bool russianOnly);

// Считать дату в формате "ДД.ММ.ГГГГ" с проверкой корректности.
// Возвращает строку, уже прошедшую проверку.
std::string readDate(std::istream& in,
                     const std::string& prompt);

#endif // LAB4_INPUT_UTILS_H


