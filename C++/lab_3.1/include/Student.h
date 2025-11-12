//
// Created by jegorix on 15.10.25.
//

#ifndef LAB_3_1_STUDENT_H
#define LAB_3_1_STUDENT_H

#pragma once
#include "Uchaschiysya.h"

class Student : public Uchaschiysya {
protected:
    int course; // курс студента

public:
    Student() : Uchaschiysya() {
        course = 0;
    }

    Student(char* name) : Uchaschiysya(name) {
        course = 1;
    }

    Student(Student& other) : Uchaschiysya(other) {
        course = other.course;
    }

    ~Student() {}

    int getCourse();
    void setCourse(int new_course);

    void showMenu() override;
    void printHeader() const override;
    void printTable() const override;

    Student& operator = (const Student& object);
    friend std::ostream& operator << (std::ostream& os, const Student& object);
    friend std::istream& operator >> (std::istream& is, Student& object);
};

#endif //LAB_3_1_STUDENT_H