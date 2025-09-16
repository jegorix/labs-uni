//
// Created by jegorix on 7.09.25.
//

#ifndef LAB1_STRINGARRAY_H
#define LAB1_STRINGARRAY_H
#include <string>
#include <cstring>

class StringArray
{
private:
    char* string;
    static int objectCount;

    // implem methods
    char* allocateAndCopy(const char* str);
    void freeMemory();

public:
    // constr
    StringArray();
    StringArray(const char* str);
    StringArray(const StringArray& other);

    // destr
    ~StringArray();

    // assign opera
    StringArray& operator=(const StringArray& other);

    // sub operator
    int operator-(const StringArray& other) const;

    // getters
    char* getString() const;
    int getLength() const;

    // setters
    void setString(const char* str);

    // public methods
    bool isEmpty() const;
    void printString() const;
    void clearString();

    // static methods
    static int getObjectCount();
};

#endif //LAB1_STRINGARRAY_H