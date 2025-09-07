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
    char* string1;
    char* string2;
    static int objectCount;

    // implementation methods
    char* allocateAndCopy(const char* str);
    void freeMemory();

public:
    // constructors
    StringArray();
    StringArray(const char* string1, const char* string2);
    StringArray(const StringArray& other);
    //destructors
    ~StringArray();

    // assign oper
    StringArray& operator=(const StringArray& other);


    // getters
    char* getFirstString() const;
    char* getSecondString() const;
    int getFirstLength() const;
    int getSecondLength() const;

    //setters
    void setFirstString(std::string str);
    void setFirstString(const char* str);
    void setSecondString(std::string str);
    void setSecondString(const char* str);

    //public methods
    int calculateStringSub() const;
    int calculateTotalLength() const;

    bool isEmpty() const;
    void swapStrings();
    void printStrings() const;

    //static methods
    static int getObjectCount();

};


#endif //LAB1_STRINGARRAY_H
