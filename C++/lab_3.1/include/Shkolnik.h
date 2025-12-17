//
// Created by jegorix on 15.10.25.
//

#ifndef LAB_3_1_SHKOLNIK_H
#pragma once
#include "Uchaschiysya.h"

class Shkolnik : public Uchaschiysya {
protected:
    int grade;

public:
    Shkolnik() : Uchaschiysya() {
        grade = 0;
    }

    Shkolnik(char* name) : Uchaschiysya(name) {
        grade = 1;
    }

    Shkolnik(Shkolnik& other) : Uchaschiysya(other) {
        grade = other.grade;
    }

    ~Shkolnik() {}

    int getGrade();
    void setGrade(int new_grade);

    // переопределенные методы из базового класса
    void showMenu() override;

    Shkolnik& operator = (const Shkolnik& object);
    friend std::ostream& operator << (std::ostream& os, const Shkolnik& object);
    friend std::istream& operator >> (std::istream& is, Shkolnik& object);
};

#endif //LAB_3_1_SHKOLNIK_H