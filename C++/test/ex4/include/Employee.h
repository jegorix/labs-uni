#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <string>


class Employee
{
    private:
        int id;
        std::string name;
        std::string position;
        double salary;
        std::string department;

    public:
        Employee();
        Employee(int id, const std::string& name, const std::string& position,
             double salary, std::string& department);

        int getId() const;
        std::string getName() const;
        std::string getPosition() const;
        double getSalary() const;
        std::string getDepartment() const;

        void setId(int newId);
        void setName(const std::string& newName);
        void setPosition(const std::string& newPosition);
        void setSalary(double newSalary);
        void setDepartment(const std::string& newDepartment);

        void display() const;

        friend std::ostream& operator<<(std::ostream& os, const Employee& emp);

        bool operator==(const Employee& other) const;
        bool operator<(const Employee& other) const;

        bool operator!=(const Employee& other) const;
        bool operator>(const Employee& other) const;
        bool operator<=(const Employee& other) const;
        bool operator>=(const Employee& other) const;

};

#endif