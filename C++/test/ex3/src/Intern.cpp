#include "Intern.h"
Intern::Intern() : Employee(), mentorId(0) {};
Intern::Intern(int id, std::string name, double salary, int mentorId)
    : Employee(id, name, salary), mentorId(mentorId) {};

Intern::Intern(const Intern &other) : Employee(other), mentorId(other.mentorId) {};
Intern::~Intern() {};

double Intern::CalculateBonus() const
{
    return 0;
}