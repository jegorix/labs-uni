#ifndef MONEY_H
#define MONEY_H

#include <iostream>
#include <string>

class Money{
    private:
        int nominal;
        int coin;

    public:
        Money();
        Money(int nominal, int coin);
        Money(const Money& other);

        Money operator+(const Money& other) const;
        Money operator-(const Money& other) const;
        Money operator*(int factor) const;
        Money operator/(int divisor) const;
        bool operator==(const Money& other) const;
        bool operator!=(const Money& other) const;
        bool operator>(const Money& other) const;
        bool operator<(const Money& other) const;
        Money& operator+=(const Money& other);
        Money& operator-=(const Money& other);
        void print() const;

        friend std::ostream& operator<<(std::ostream& os, const Money& m);
        friend std::istream& operator>>(std::istream& is, Money& m);

};

#endif