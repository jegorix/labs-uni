#include "../include/string_subtraction/StringArray.h"
#include <iostream>
#include <cstring>
#include <algorithm>

int StringArray::objectCount = 0;

// Private methods
char* StringArray::allocateAndCopy(const char* str) {
    if(str == nullptr) {
        char* empty = new char[1];
        empty[0] = '\0';
        return empty;
    }
    size_t length = strlen(str);
    char* buffer = new char[length + 1];
    strcpy(buffer, str);
    return buffer;
}

void StringArray::freeMemory() {
    delete[] string;
    string = nullptr;
}

// Constructors
StringArray::StringArray() : string(nullptr) {
    this->string = new char[1];
    this->string[0] = '\0';
    objectCount++;
}

StringArray::StringArray(const char* str) {
    this->string = allocateAndCopy(str);
    objectCount++;
}

StringArray::StringArray(const StringArray& other) {
    string = allocateAndCopy(other.string);
    objectCount++;
}

// destructor
StringArray::~StringArray() {
    freeMemory();
    objectCount--;
}

// assign operator
StringArray& StringArray::operator=(const StringArray& other) {
    if(this != &other) {
        freeMemory();
        this->string = allocateAndCopy(other.string);
    }
    return *this;
}

// sub oper
int StringArray::operator-(const StringArray& other) const {
    int len1 = string ? strlen(string) : 0;
    int len2 = other.string ? strlen(other.string) : 0;
    return len1 - len2;
}

// Getters
char* StringArray::getString() const {
    return this->string;
}

int StringArray::getLength() const {
    return string ? strlen(string) : 0;
}

// Setters
void StringArray::setString(const char* str) {
    freeMemory();
    this->string = allocateAndCopy(str);
}

// Public methods
bool StringArray::isEmpty() const {
    return string == nullptr || strlen(string) == 0;
}

void StringArray::printString() const {
    std::cout << "\n╭──────────────────────────────╮\n"
              << "│         Содержимое:          │\n"
              << "╰──────────────────────────────╯\n";

    std::cout << "╭──────────────────────────────────╮\n";
    std::cout << "│  Строка: "
              << "                              \n"
              << "\n   " << (this->string ? this->string : "Строка пуста!") << "\n";
    std::cout << "╰──────────────────────────────────╯\n";
}

void StringArray::clearString() {
    freeMemory();
    this->string = new char[1];
    this->string[0] = '\0';
}

// static method
int StringArray::getObjectCount() {
    return objectCount;
}