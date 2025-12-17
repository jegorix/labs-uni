#pragma once
#include <iostream>
#include <string>

struct Date {
    int day;
    int month;
    int year;
    
    Date();
    Date(int d, int m, int y);
    
    bool isValid() const;
    std::string toString() const;
    
    friend std::ostream& operator<<(std::ostream& os, const Date& date);
    friend std::istream& operator>>(std::istream& is, Date& date);
    
    bool operator==(const Date& other) const;
    bool operator<(const Date& other) const;
};



