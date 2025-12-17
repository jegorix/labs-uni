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

    Shkolnik(const Shkolnik& other) : Uchaschiysya(other) {
        grade = other.grade;
    }

    ~Shkolnik() {}

    int getGrade();
    int getGrade() const;
    void setGrade(int new_grade);

    void showMenu() override;
    void printHeader() const override;
    void printTable() const override;

    Shkolnik& operator = (const Shkolnik& object);
    friend std::ostream& operator << (std::ostream& os, const Shkolnik& object);
    friend std::istream& operator >> (std::istream& is, Shkolnik& object);

    // Перегрузка оператора сравнения == для поиска (по имени, возрасту и классу)
    bool operator == (const Shkolnik& other) const;

    // Работа с файлами
    struct BinaryRecord {
        char name[NAME_CAP];
        int age;
        int grade;
    };
    void saveTextRecord(std::ostream& os);
    static Shkolnik* readTextRecord(std::istream& is);
    void saveBinaryRecord(std::ostream& os);
    static Shkolnik* readBinaryRecord(std::istream& is);
};

#endif //LAB_3_1_SHKOLNIK_H
