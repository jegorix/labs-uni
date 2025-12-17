#include <iostream>
#include <string>
#include "Student.h"

Student::Student(std::string name, int age, float grade) {
    this->name = name;
    this->age = age;
    this->grade = grade;
}

void Student::showInfo() {
    std::cout << "Name: " << name << "\n"
              << "Age: " << age << "\n"
              << "Grade: " << grade << std::endl;
}

void Student::setAge(int a) {
    age = a;
}

void Student::setGrade(float gr) {
    grade = gr;
}



int Student::getAge() { return age; }
float Student::getGrade() { return grade; }