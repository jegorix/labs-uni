#include "MyString.h"

// Конструктор по умолчанию
MyString::MyString() : data("") {}

// Конструктор из const char*
MyString::MyString(const char* str) : data(str) {}

// Конструктор из std::string
MyString::MyString(const std::string& str) : data(str) {}

// Конструктор копирования
MyString::MyString(const MyString& other) : data(other.data) {}

// Оператор присваивания
MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        data = other.data;
    }
    return *this;
}

// Доступ к символам по индексу
char& MyString::operator[](int index) {
    return data[index];
}

const char& MyString::operator[](int index) const {
    return data[index];
}

// Оператор () для выделения подстроки
MyString MyString::operator()(int start, int length) const {
    return MyString(data.substr(start, length));
}


// Сравнение по длине строк
bool MyString::operator>(const MyString& other) const {
    return data.size() > other.data.size();
}

bool MyString::operator<(const MyString& other) const {
    return data.size() < other.data.size();
}

// Конкатенация (MyString + MyString)
MyString MyString::operator+(const MyString& other) const {
    return MyString(data + other.data);
}

// Конкатенация (MyString + std::string)
MyString MyString::operator+(const std::string& other) const {
    return MyString(data + other);
}

// Конкатенация (std::string + MyString)
MyString operator+(const std::string& lhs, const MyString& rhs) {
    return MyString(lhs + rhs.data);
}

// Конкатенация (MyString + const char*)
MyString MyString::operator+(const char* other) const {
    return MyString(data + other);
}

// Конкатенация (const char* + MyString)
MyString operator+(const char* lhs, const MyString& rhs) {
    return MyString(lhs + rhs.data);
}

// Оператор +=
MyString& MyString::operator+=(const MyString& other) {
    data += other.data;
    return *this;
}

// Префиксный ++ (сдвигаем каждый символ на 1)
MyString& MyString::operator++() {
    for (int i = 0; i < (int)data.size(); i++) {
        if (data[i] != '\0') {
            data[i] = data[i] + 1;
        }
    }
    return *this; // возвращаем изменённый объект
}

// Постфиксный ++
MyString MyString::operator++(int) {
    MyString temp(*this); // сохраняем старое значение
    ++(*this);            // применяем префиксный ++ к текущему объекту
    return temp;          // возвращаем старую копию
}

// Префиксный -- (сдвигаем каждый символ на -1)
MyString& MyString::operator--() {
    for (int i = 0; i < (int)data.size(); i++) {
        if (data[i] != '\0') {
            data[i] = data[i] - 1;
        }
    }
    return *this; // возвращаем изменённый объект
}

// Постфиксный --
MyString MyString::operator--(int) {
    MyString temp(*this); // сохраняем старое значение
    --(*this);            // применяем префиксный -- к текущему объекту
    return temp;          // возвращаем старую копию
}

// Перегрузка вывода
std::ostream& operator<<(std::ostream& os, const MyString& str) {
    os << str.data;
    return os;
}

// Перегрузка ввода
std::istream& operator>>(std::istream& is, MyString& str) {
    is >> str.data;
    return is;
}