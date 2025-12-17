#include "Employee.h"

Employee::Employee() : id(0), name("None"), salary(0.0) {};
Employee::Employee(int id, std::string name, double salary) : id(id), name(name), salary(salary) {};
Employee::Employee(const Employee &other)
{
    this->id = other.id;
    this->name = other.name;
    this->salary = other.salary;
}
Employee::~Employee() {};

void Employee::displayInfo()
{
    std::cout << "ID: " << id << "\nName: " << name << "\nSalary: " << salary << std::endl;
}

void Employee::getAnnualSalary() const
{
    std::cout << "Annual Salary: " << salary * 12 << std::endl;
}
