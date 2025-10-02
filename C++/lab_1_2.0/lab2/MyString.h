#pragma once
#include <iostream>
#include <string>

class MyString {
private:
    std::string data;

public:
    // Конструктор по умолчанию
    MyString();

    // Конструктор с параметром для строки char*
    explicit MyString(const char* str);

    // Конструктор с параметром для string
    explicit MyString(const std::string& str);

    // Конструктор копирования
    MyString(const MyString& other);

    // Оператор присваивания
    MyString& operator=(const MyString& other);

    // Доступ к символам по индексу
    char& operator[](int index);
    const char& operator[](int index) const;

    // Оператор () для выделения подстроки
    MyString operator()(int start, int length) const;

    // Сравнение
    bool operator>(const MyString& other) const;
    bool operator<(const MyString& other) const;

    //  (MyString + MyString)
    MyString operator+(const MyString& other) const;

    //  (MyString + std::string)
    MyString operator+(const std::string& other) const;

    //  (std::string + MyString)
    friend MyString operator+(const std::string& lhs, const MyString& rhs);

    //  (MyString + const char*)
    MyString operator+(const char* other) const;

    //  (const char* + MyString)
    friend MyString operator+(const char* lhs, const MyString& rhs);

    // Оператор +=
    MyString& operator+=(const MyString& other);

    // Префиксный ++ (сдвигаем все символы на 1)
    MyString& operator++();

    // Постфиксный ++
    MyString operator++(int);

    // Префиксный --
    MyString& operator--();

    // Постфиксный --
    MyString operator--(int);

    // Перегрузка ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const MyString& str);
    friend std::istream& operator>>(std::istream& is, MyString& str);
};