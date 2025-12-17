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

        void print() const;

        friend std::ostream& operator<<(std::ostream& os, const Money& m);
};

#endif