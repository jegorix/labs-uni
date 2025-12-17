#include "Employee.h"
#include <iomanip>


Employee::Employee() 
    : id(0), name("Unknown"), position("Unknown"), 
      salary(0.0), department("Unknown") {}

Employee::Employee(int id, const std::string& name, const std::string& position, 
                   double salary, const std::string& department)
    : id(id), name(name), position(position), 
      salary(salary), department(department) {}


int Employee::getId() const
{
    return id;
}

std::string Employee::getName() const
{
    return name;
}

std::string Employee::getPosition() const 
{
    return position;
}

double Employee::getSalary() const
{
    return salary;
}

std::string Employee::getDepartment() const 
{
    return department;
}

void Employee::setId(int newId)
{
    id = newId;
}

void Employee::setName(std::string& newName)
{
    name = newName;
}

void Employee::setPosition(std::string& newPosition)
{
    position = newPosition;
}

void Employee::setSalary(double newSalary)
{
    salary = newSalary;
}

void Employee::setDepartment(const std::string& newDepartment)
{
    department = newDepartment;
}


void Employee::display() const
{
        std::cout << "ID: " << id 
              << ", Name: " << name
              << ", Position: " << position
              << ", Salary: $" << std::fixed << std::setprecision(2) << salary
              << ", Department: " << department;
}

std::ostream& operator<<(std::ostream& os, const Employee& emp)
{
    os << emp.id << ": " << emp.name << " (" << emp.position 
       << ") - $" << std::fixed << std::setprecision(2) << emp.salary
       << " [" << emp.department << "]";
    return os;
}

bool Employee::operator==(const Employee& other) const
{
    return id == other.id;
}

bool Employee::operator<(const Employee& other) const
{
    return salary > other.salary;
}

bool Employee::operator!=(const Employee& other) const
{
    return !(*this == other);
}

bool Employee::operator>(const Employee& other) const
{
    return other < *this;
}

bool Employee::operator<=(const Employee& other) const
{
    return !(other < *this);
}

bool Employee::operator>=(const Employee& other) const 
{
    return !(*this < other);
}

