//
// Created by jegorix on 7.09.25.
//

#include "../include/string_subtraction/StringArray.h"
#include <cstring>
#include <iostream>
#include <algorithm>

int StringArray::objectCount = 0;


char* StringArray::allocateAndCopy(const char* str)
{
    if(str == nullptr)
    {
        char* empty = new char[1];
        empty[0] = '\0';
        return empty;
    }
    size_t length = strlen(str);
    char* buffer = new char[length + 1];
    strcpy(buffer, str);
    return buffer;
}


void StringArray::freeMemory()
{
    delete[] this->string1;
    delete[] this->string2;
    this->string1 = nullptr;
    this->string2 = nullptr;
}

// default cons
StringArray::StringArray(): string1(nullptr), string2(nullptr)
{
    this->string1 = new char[1]; this->string1[0] = '\0';
    this->string2 = new char[1]; this->string2[0] = '\0';
    objectCount++;
}
// param cons
StringArray::StringArray(const char* str1, const char* str2)
{
    this->string1 = allocateAndCopy(str1);
    this->string2 = allocateAndCopy(str2);
    objectCount++;
}
// copy cons
// for assign when init
StringArray::StringArray(const StringArray& other)
{
    string1 = allocateAndCopy(other.string1);
    string2 = allocateAndCopy(other.string2);
}

StringArray::~StringArray()
{
    freeMemory();
    objectCount--;
}

// for already init objects
StringArray& StringArray::operator=(const StringArray& other)
{
    if(this != &other) // this pointer
    {
        freeMemory();
        this->string1 = allocateAndCopy(other.string1);
        this->string2 = allocateAndCopy(other.string2);
    }
    return *this;
}

// getters
char* StringArray::getFirstString() const
{
    return this->string1;
}

char* StringArray::getSecondString() const
{
    return this->string2;
}

int StringArray::getFirstLength() const {
    return strlen(this->string1);
}

int StringArray::getSecondLength() const {
    return strlen(this->string2);
}

// setters
void StringArray::setFirstString(const char *str)
{
    delete[] this->string1;
    this->string1 = allocateAndCopy(str);
}

void StringArray::setSecondString(const char *str) {
    delete[] this->string2;
    this->string2 = allocateAndCopy(str);
}

// custom methods
int StringArray::calculateStringSub() const
{
    return strlen(this->string1) - strlen(this->string2);
}

int StringArray::calculateTotalLength() const
{
    return strlen(this->string1) + strlen(this->string2);
}

bool StringArray::isEmpty() const
{
    return (strlen(this->string1) == 0 && strlen(this->string2) == 0);
}

void StringArray::swapStrings()
{
    std::swap(string1, string2);
}

int StringArray::getObjectCount()
{
    return objectCount;
}

void StringArray::printStrings() const
{
 std::cout << "\n╭──────────────────────────────╮\n"
                "│         Содержимое:          │\n"
                "╰──────────────────────────────╯\n";

    std::cout << "╭──────────────────────────────────╮\n";
    std::cout << "│  Строка №1: "
              << "                              \n"
             <<"\n   "<< (this->string1 ? this->string1 : "Строка №1 пуста!") << "\n";
    std::cout << "╰──────────────────────────────────╯\n";

    std::cout << "╭──────────────────────────────────╮\n";
    std::cout << "│  Строка №2: "
              << "                              \n"
            <<"\n   "<< (this->string2 ? this->string2 : "Строка №2 пуста!") << "\n";
    std::cout << "╰──────────────────────────────────╯\n";
}

void StringArray::clearStrings()
{
    freeMemory();
    string1 = nullptr;
    string2 = nullptr;
}