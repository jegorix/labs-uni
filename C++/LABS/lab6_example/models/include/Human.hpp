#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "../../exceptions/include/Date.hpp"

using namespace std;

enum SearchMode {
    FULL_MATCH,
    LAST_NAME,
    FIRST_NAME,
    MIDDLE_NAME,
    BIRTH_YEAR
};

class Human {
protected:
    string firstName;
    string lastName;
    string middleName;
    Date birthday;
    static SearchMode currentSearchMode;
public:
    Human();
    Human(const string& first, const string& last, const string& middle, const Date& birth);
    virtual ~Human();
    Human(const Human& other);
    Human& operator=(const Human& other);

    string getFirstName() const;
    string getLastName() const;
    string getMiddleName() const;
    Date getBirthday() const;

    void setFirstName(const string& first);
    void setLastName(const string& last);
    void setMiddleName(const string& middle);
    void setBirthday(const Date& birth);

    static void setSearchMode(SearchMode mode);
    static SearchMode getSearchMode();

    bool operator==(const Human& other) const;
    bool operator<(const Human& other) const;

    virtual void printHeader() const;
    virtual void printTable() const;

    virtual void updateField(int fieldChoice);

    void saveTextRecord(ostream& os) const;
    static Human* readTextRecord(istream& is);

    void saveBinaryRecord(ostream& os) const;
    static Human* readBinaryRecord(istream& is);

    friend ostream& operator<<(ostream& os, const Human& member);
    friend istream& operator>>(istream& is, Human& member);
};
