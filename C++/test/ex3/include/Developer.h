#ifndef DEVELOPER_H
#define DEVELOPER_H
#include "Employee.h"
#include <iostream>
#include <string>

class Developer: protected Employee
{
    private:
        std::string programmingLanguage;
    public:
        Developer();
        Developer(int id, std::string name, double salary, std::string programminLanguage);
        Developer(const Developer &other);
        ~Developer();

        double CalculateBonus() const override;
        void displayInfo() override;
};

#endif