#include "Developer.h"

Developer::Developer() : Employee(), programmingLanguage("None") {};
Developer::Developer(int id, std::string name, double salary, std::string programmingLanguage)
    : Employee(id, name, salary), programmingLanguage(programmingLanguage) {};

Developer::Developer(const Developer &other) : Employee(other)
{
    this->programmingLanguage = other.programmingLanguage;
}

Developer::~Developer() {};

double Developer::CalculateBonus() const 
{
    int extra;
    if (programmingLanguage == "C++")
    {
        extra = 1000;
    }
    else
    {
        extra = 500;
    }

    return getSalary() * 0.15 + extra;
}

void Developer::displayInfo()
{
    Employee::displayInfo();
    std::cout << "Programming Language: " << programmingLanguage << std::endl;
}