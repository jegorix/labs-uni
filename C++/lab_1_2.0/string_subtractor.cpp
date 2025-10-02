#include "string_subtractor.h"
#include <cstring>

// Конструктор по умолчанию
StringSub::StringSub() {
    text = new char[1];
    text[0] = '\0';
}

// Конструктор c параметром
StringSub::StringSub(const char* s) {
    text = new char[strlen(s) + 1];
    strcpy(text, s);
}

// Конструктор копирования
StringSub::StringSub(const StringSub& other) {
    text = new char[strlen(other.text) + 1];
    strcpy(text, other.text);
}

// Оператор присваивания
StringSub& StringSub::operator=(const StringSub& other) {
    if (this != &other) {
        delete[] text;
        text = new char[strlen(other.text) + 1];
        strcpy(text, other.text);
    }
    return *this;
}

// Деструктор
StringSub::~StringSub() {
    delete[] text;
}

// Подсчёт длины строки (UTF-8)
int StringSub::length() const {
    int count = 0;
    for (const unsigned char* p = (unsigned char*)text; *p; ++p)
        if ((*p & 0xC0) != 0x80) // считаем только первые байты символов
            ++count;
    return count;
}


// Оператор вычитания
int StringSub::operator-(const StringSub& other) const {
    return length() - other.length();
}

// Перегрузка оператора ввода
std::istream& operator>>(std::istream& in, StringSub& s) {
    char buffer[1024];
    in.getline(buffer, 1024);
    delete[] s.text;
    s.text = new char[strlen(buffer) + 1];
    strcpy(s.text, buffer);
    return in;
}

// Перегрузка оператора вывода
std::ostream& operator<<(std::ostream& out, const StringSub& s) {
    out << s.text;
    return out;
}