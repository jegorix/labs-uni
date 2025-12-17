#ifndef INTERN_H
#define INTERN_H
#include "Employee.h"
#include <iostream>
#include <string>

class Intern: protected Employee
{
    private:
        int mentorId;
    public:
        Intern();
        Intern(int id, std::string name, double salary, int mentorId);
        Intern(const Intern &other);
        ~Intern();

        double CalculateBonus() const override;
        void displayInfo() override;
};

#endif