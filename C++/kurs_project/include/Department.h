// Department.h
#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <string>
#include <iostream>

class Department {
private:
    int id;
    std::string name;
    int capacity;
    double budget;

public:
    Department();
    Department(int id, std::string name, int cap, double bud);
    Department(const Department& other);
    ~Department();
    Department& operator=(const Department& other);
    void print(std::ostream&) const;
    void read(std::istream&);
    void serializeBinary(std::ostream&) const;
    void deserializeBinary(std::istream&);
    int getId() const;
    void setId(int);
    std::string getName() const;
    void setName(std::string);
    int getCapacity() const;
    void setCapacity(int);
    double getBudget() const;
    void setBudget(double);
    friend std::ostream& operator<<(std::ostream&, const Department&);
    friend std::istream& operator>>(std::istream&, Department&);
};

#endif // DEPARTMENT_H