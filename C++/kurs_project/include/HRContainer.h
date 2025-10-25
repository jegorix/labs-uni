// HRContainer.h
#ifndef HRCONTAINER_H
#define HRCONTAINER_H

#include "Person.h"
#include "Department.h"
#include "Position.h"
#include <vector>
#include <memory>
#include <cstddef>

class HRContainer {
private:
    std::vector<std::unique_ptr<Person>> employees;
    std::vector<Department> departments;
    std::vector<Position> positions;
    int nextId;

public:
    class EmployeeIterator {
    private:
        HRContainer* c;
        size_t idx;

    public:
        EmployeeIterator(HRContainer* c, size_t idx);
        Person& operator*() const;
        EmployeeIterator& operator++();
        bool operator!=(const EmployeeIterator& other) const;
    };

    HRContainer();
    HRContainer(const HRContainer& other);
    HRContainer& operator=(const HRContainer& other);
    int generateId();
    void addEmployee(std::unique_ptr<Person>);
    std::unique_ptr<Person> removeEmployeeById(int);
    Person* findEmployeeById(int);
    void addDepartment(Department);
    void removeDepartmentById(int);
    Department* findDepartmentById(int);
    void addPosition(Position);
    void removePositionById(int);
    Position* findPositionById(int);
    void clear();
    size_t employeeSize() const;
    void saveBinary(std::string filename);
    void loadBinary(std::string filename);
    EmployeeIterator beginEmployees();
    EmployeeIterator endEmployees();
    void sortEmployeesBySalary();
    Person* searchEmployee(std::string criteria);
};

#endif // HRCONTAINER_H