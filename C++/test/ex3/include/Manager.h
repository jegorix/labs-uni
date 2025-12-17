#ifndef MANAGER_H
#define MANAGER_H
#include "Employee.h"
#include <iostream>
#include <string>

class Manager: protected Employee
{
    private:
        int teamSize;

    public:
        Manager();
        Manager(int id, std::string name, double salary, int teamSize);
        Manager(const Manager &other);
        ~Manager();

        double CalculateBonus() const override;
        void displayInfo() override;

};
 
#endif