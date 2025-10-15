//
// Created by jegorix on 15.10.25.
//

#ifndef LAB_3_1_UCHASCHIYSYA_H

#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cmath>
#include <cstring>
#include <limits>
#include <cstdlib>
#include <iomanip>
#include <typeinfo>

class Uchaschiysya
{
protected:
    char name[32];
    int age;

public:
    Uchaschiysya()
    {
        name[0] = '\0';
        age = 0;
    }

    Uchaschiysya(char* name)
    {
        strcpy(this->name, name);
        age = 0;
    }

    Uchaschiysya(Uchaschiysya& other)
    {
        strcpy(name, other.name);
        age = other.age;
    }

    ~Uchaschiysya() {}

    char* getName();
    int getAge();

    void setName(char* new_name);
    void setAge(int new_age);

    virtual void showMenu();

    Uchaschiysya& operator = (const Uchaschiysya& object);
    friend std::ostream& operator << (std::ostream& os, const Uchaschiysya& object);
    friend std::istream& operator >> (std::istream& is, Uchaschiysya& object);
};

#endif //LAB_3_1_UCHASCHIYSYA_H
