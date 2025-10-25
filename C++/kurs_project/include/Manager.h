// Manager.h
#ifndef MANAGER_H
#define MANAGER_H

#include "Employee.h"
#include <string>
#include <memory>
#include <iostream>

class Manager : public Employee {
private:
    std::string managedDepartment;

public:
    Manager();
    Manager(std::string n, std::string s, int a, int id, double sal, std::string pos, std::string dep, std::string md);
    Manager(const Manager& other);
    ~Manager();
    Manager& operator=(const Manager& other);
    std::unique_ptr<Person> clone() const override;
    void print(std::ostream&) const override;
    void read(std::istream&) override;
    void serializeBinary(std::ostream&) const override;
    void deserializeBinary(std::istream&) override;
    std::string getManagedDepartment() const;
    void setManagedDepartment(std::string);
    friend std::ostream& operator<<(std::ostream&, const Manager&);
    friend std::istream& operator>>(std::istream&, Manager&);
};

#endif // MANAGER_H