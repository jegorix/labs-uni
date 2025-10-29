// Person.h
#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <memory>
#include <iostream>

class Person {
protected:
    std::string name;
    std::string surname;
    int age;

public:
    Person();
    Person(std::string n, std::string s, int a);
    Person(const Person& other);
    virtual ~Person();
    Person& operator=(const Person& other);
    virtual std::unique_ptr<Person> clone() const = 0;
    virtual void print(std::ostream&) const;
    virtual void read(std::istream&);
    virtual void serializeBinary(std::ostream&) const;
    virtual void deserializeBinary(std::istream&);
    std::string getName() const;
    void setName(std::string);
    std::string getSurname() const;
    void setSurname(std::string);
    int getAge() const;
    void setAge(int);
    friend std::ostream& operator<<(std::ostream&, const Person&);
    friend std::istream& operator>>(std::istream&, Person&);
};

#endif // PERSON_H