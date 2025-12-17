#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <iostream>
#include <string>

class Employee 
{
    private:
        int id;
        std::string name;
        double salary;

    public:
        Employee();
        Employee(int id, std::string name, double salary);
        Employee(const Employee &other);
        ~Employee();

        virtual double CalculateBonus() const = 0;
        virtual void displayInfo();
        void getAnnualSalary() const;

        int getId() const {return id;}
        std::string getName() const {return name;}
        double getSalary() const {return salary;}
};

#endif