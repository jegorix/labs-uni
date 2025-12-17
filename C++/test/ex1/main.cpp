#include <iostream>
#include "include/Student.h"
#include "include/Money.h"

int main()
{
    // std::cout << "Hello world" << std::endl;
    // Student student1("Tom", 16, 8.5);
    // Student student2("John", 12, 8.9);
    // Student student3("Ben", 17, 8.1);

    // student1.showInfo();
    // student2.showInfo();
    
    // student3.getAge();

    // student1.setAge(19);
    // student1.getAge();

    // student3.setGrade(8.2);
    // student3.getGrade();

    Money mon1(12, 25);
    Money mon2(13, 47);

    Money mon3 = mon1 + mon2;

    std::cout << "money1: " << mon1 << std::endl;
    std::cout << "money2: " << mon2 << std::endl;
    std::cout << "money1 + money2 = " << mon3 << std::endl;


    return 0;
}