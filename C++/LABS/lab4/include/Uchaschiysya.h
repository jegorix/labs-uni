//
// Created by jegorix on 15.10.25.
//

#ifndef LAB_3_1_UCHASCHIYSYA_H
#define LAB_3_1_UCHASCHIYSYA_H

#pragma once

#include <iostream>
#include <cstddef>
#include <string>
#include <cstring>
#include <iomanip>

class Uchaschiysya {
public:
    static constexpr std::size_t NAME_CAP = 64; // максимум 63 символа + '\0'
    static constexpr int TABLE_WIDTH = 60;
    static constexpr int NAME_COL_WIDTH = 32;
    static constexpr int AGE_COL_WIDTH = 10;
    static constexpr int EXTRA_COL_WIDTH = 8;

protected:
    char name[NAME_CAP];  // строка для ФИО
    int age;              // возраст учащегося
    static std::string truncateName(const char* src);

public:
    // Конструктор по умолчанию
    Uchaschiysya() {
        name[0] = '\0';  // делаем имя пустым
        age = 0;         // возраст = 0
    }

    // Конструктор с параметром (принимает имя)
    Uchaschiysya(char* name) {
        strcpy(this->name, name); // копируем имя
        age = 0;                  // возраст не задаём
    }

    // Конструктор копирования
    Uchaschiysya(const Uchaschiysya& other) {
        strcpy(name, other.name); // копируем имя
        age = other.age;          // копируем возраст
    }

    // Деструктор
    ~Uchaschiysya() {}

    // Геттеры
    char* getName();
    int getAge();
    // Константные геттеры (для вызовов на const объектах)
    const char* getName() const;
    int getAge() const;

    // Сеттеры
    void setName(char* new_name);
    void setAge(int new_age);

    // Виртуальная функция (можно переопределять в наследниках)
    virtual void printHeader() const;
    virtual void printTable() const;
    virtual void showMenu();

    // Перегрузка оператора присваивания "="
    Uchaschiysya& operator = (const Uchaschiysya& object);

    // Перегрузка оператора вывода (cout << obj)
    friend std::ostream& operator << (std::ostream& os, const Uchaschiysya& object);

    // Перегрузка оператора ввода (cin >> obj)
    friend std::istream& operator >> (std::istream& is, Uchaschiysya& object);

    // Перегрузка оператора сравнения == для поиска (по имени и возрасту)
    bool operator == (const Uchaschiysya& other) const;
};

#endif //LAB_3_1_UCHASCHIYSYA_H
