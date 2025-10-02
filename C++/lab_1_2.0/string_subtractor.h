#pragma once
#include <iostream>

class StringSub {
private:
    char* text;

public:
    StringSub();                         // конструктор по умолчанию
    StringSub(const char* str);          // конструктор c параметром
    StringSub(const StringSub& other);   // конструктор копирования
    ~StringSub();                        // деструктор

    StringSub& operator=(const StringSub& other); // оператор присваивания

    int length();                  // длина строки

    int operator-(const StringSub& other);  // разница длин

    // Перегрузка ввода/вывода
    friend std::istream& operator>>(std::istream& in, StringSub& s);
    friend std::ostream& operator<<(std::ostream& out, const StringSub& s);
};