#include <iostream>
#include "Money.h"

Money::Money() {
    nominal = 0;
    coin = 0;
}

Money::Money(int nominal, int coin)
{
    this->nominal = nominal;
    this->coin = coin;
}

Money::Money(const Money& other)
{
    this->nominal = other.nominal;
    this->coin = other.coin;
}

Money Money::operator+(const Money& other) const
{
    return Money(this->nominal + other.nominal, this->coin + other.coin);
}

void Money::print() const {
    std::cout << nominal << "." << coin << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Money& other)
{
    os << "Amount: " << other.nominal << "." << other.coin;
    return os;
}
