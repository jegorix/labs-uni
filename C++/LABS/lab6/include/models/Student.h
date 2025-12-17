//
// Created by jegorix on 15.10.25.
//

#ifndef LAB_3_1_STUDENT_H
#define LAB_3_1_STUDENT_H

#pragma once
#include "Uchaschiysya.h"

class Student : public Uchaschiysya {
protected:
    int course;

public:
    Student() : Uchaschiysya() {
        course = 0;
    }

    Student(char* name) : Uchaschiysya(name) {
        course = 1;
    }

    Student(const Student& other) : Uchaschiysya(other) {
        course = other.course;
    }

    ~Student() {}

    int getCourse();
    int getCourse() const;
    void setCourse(int new_course);

    void showMenu() override;
    void printHeader() const override;
    void printTable() const override;

    Student& operator = (const Student& object);
    friend std::ostream& operator << (std::ostream& os, const Student& object);
    friend std::istream& operator >> (std::istream& is, Student& object);

    // Перегрузка оператора сравнения == для поиска (по имени, возрасту и курсу)
    bool operator == (const Student& other) const;

    // Работа с файлами
    struct BinaryRecord {
        char name[NAME_CAP];
        int age;
        int course;
    };
    void saveTextRecord(std::ostream& os);
    static Student* readTextRecord(std::istream& is);
    void saveBinaryRecord(std::ostream& os);
    static Student* readBinaryRecord(std::istream& is);
};

#endif //LAB_3_1_STUDENT_H
