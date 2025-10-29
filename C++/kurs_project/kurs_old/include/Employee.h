// Employee.h
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "Person.h"
#include <string>
#include <memory>
#include <iostream>

class Employee : public Person {
private:
    int id;
    double salary;
    std::string positionId;
    std::string departmentId;

public:
    Employee();
    Employee(std::string n, std::string s, int a, int id, double sal, std::string pos, std::string dep);
    Employee(const Employee& other);
    ~Employee();
    Employee& operator=(const Employee& other);
    std::unique_ptr<Person> clone() const override;
    void print(std::ostream&) const override;
    void read(std::istream&) override;
    void serializeBinary(std::ostream&) const override;
    void deserializeBinary(std::istream&) override;
    int getId() const;
    void setId(int);
    double getSalary() const;
    void setSalary(double);
    std::string getPositionId() const;
    void setPositionId(std::string);
    std::string getDepartmentId() const;
    void setDepartmentId(std::string);
    friend std::ostream& operator<<(std::ostream&, const Employee&);
    friend std::istream& operator>>(std::istream&, Employee&);
};

#endif // EMPLOYEE_H