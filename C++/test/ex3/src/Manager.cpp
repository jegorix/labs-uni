#include "Manager.h"

Manager::Manager() : Employee(), teamSize(0) {};
Manager::Manager(int id, std::string name, double salary, int teamSize)
    : Employee(id, name, salary), teamSize(teamSize) {};

Manager::Manager(const Manager &other) : Employee(other)
{
    this->teamSize = other.teamSize;
}

Manager::~Manager() {};

double Manager::CalculateBonus() const
{
    return getSalary() * 0.2 + teamSize * 100;
}

void Manager::displayInfo()
{
    Employee::displayInfo();
    std::cout << "Team Size: " << teamSize << std::endl;
}

