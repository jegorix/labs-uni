#pragma once

#include <cstddef>
#include <iosfwd>
#include <string>

// Упрощённый ввод без исключений: возвращаем корректные значения после повторного запроса.
int readInt(std::istream& in,
            const std::string& prompt,
            int minValue,
            int maxValue);

void readName(std::istream& in,
              char* buffer,
              std::size_t bufferSize,
              const std::string& prompt,
              bool russianOnly);

// Глобальная настройка: использовать кириллицу или латиницу при вводе ФИО.
bool useRussianNames();
void setUseRussianNames(bool russian);
