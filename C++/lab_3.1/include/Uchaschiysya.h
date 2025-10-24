//
// Created by jegorix on 15.10.25.
//

#ifndef LAB_3_1_UCHASCHIYSYA_H
#define LAB_3_1_UCHASCHIYSYA_H

#pragma once

#include <iostream>
#include <cstring>
#include <iomanip>

class Uchaschiysya {
protected:
    char name[32];  // строка для имени (фиксированный размер 32 символа)
    int age;        // возраст учащегося

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
    Uchaschiysya(Uchaschiysya& other) {
        strcpy(name, other.name); // копируем имя
        age = other.age;          // копируем возраст
    }

    // Деструктор
    ~Uchaschiysya() {}

    // Геттеры
    char* getName();
    int getAge();

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
};

#endif //LAB_3_1_UCHASCHIYSYA_H