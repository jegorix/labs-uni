#include "Money.h"
#include <iostream>

Money::Money()
{
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
    int totalCoin = this->coin + other.coin;
    int extraNominal = totalCoin / 100;
    int finalCoin = totalCoin % 100;
    int finalNominal = this->nominal + other.nominal + extraNominal;
    return Money(finalNominal, finalCoin);

}

Money Money::operator-(const Money& other) const
{
    int totalCoin1 = this->nominal * 100 + this->coin;
    int totalCoin2 = other.nominal * 100 + other.coin;
    int diffCoin = totalCoin1 - totalCoin2;
    int finalNominal = diffCoin / 100;
    int finalCoin = diffCoin % 100;
    return Money(finalNominal, finalCoin);
}

Money Money::operator*(int factor) const
{
    int totalCoin = (this->nominal * 100 + this->coin) * factor;
    int finalNominal = totalCoin / 100;
    int finalCoin = totalCoin % 100;
    return Money(finalNominal, finalCoin);
}

Money Money::operator/(int divisor) const
{
    int totalCoin = (this->nominal * 100 + this->coin) / divisor;
    int finalNominal = totalCoin / 100;
    int finalCoin = totalCoin % 100;
    return Money(finalNominal, finalCoin);
}

bool Money::operator==(const Money& other) const
{
    return this->nominal == other.nominal && this->coin == other.coin;
}

bool Money::operator!=(const Money& other) const
{
    return this->nominal != other.nominal || this->coin != other.coin;
}

bool Money::operator>(const Money& other) const
{
    int total1 = this->nominal * 100 + this->coin;
    int total2 = this->nominal * 100 + this->coin;
    return total1 > total2;
}

bool Money::operator<(const Money& other) const
{
    int total1 = this->nominal * 100 + this->coin;
    int total2 = this->nominal * 100 + this->coin;
    return total1 < total2;
}

Money& Money::operator+=(const Money& other)
{
    int totalCoin = coin + other.coin;
    nominal = other.nominal + other.coin / 100;
    coin = totalCoin % 100;
    return *this;
}

Money& Money::operator-=(const Money& other)
{
    int total1 = nominal * 100 + coin;
    int total2 = other.nominal + other.coin;
    int diff = total1 - total2;
    nominal = diff / 100;
    coin = diff % 100;
    return *this;
}

void Money::print() const
{
    std::cout << nominal << "." << coin << "руб." << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Money& m)
{
    os << "Money(" << m.nominal << "." << m.coin << ")" << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, Money& m)
{
    is >> m.nominal >> m.coin;
    return is;
}