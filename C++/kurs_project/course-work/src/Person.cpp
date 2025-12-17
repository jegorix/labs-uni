#include "../include/Person.h"

Person::Person() = default;

Person::Person(const std::string& firstName, const std::string& lastName)
    : firstName(firstName), lastName(lastName) {}

Person::~Person() = default;

std::string Person::getFirstName() const {
    return firstName;
}

std::string Person::getLastName() const {
    return lastName;
}

std::string Person::getFullName() const {
    return lastName + " " + firstName;
}

void Person::setFirstName(const std::string& firstName) {
    this->firstName = firstName;
}

void Person::setLastName(const std::string& lastName) {
    this->lastName = lastName;
}

