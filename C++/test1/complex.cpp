#include "complex.h"

Complex::Complex(double r, double i) : re(r), im(i) {};

double Complex::real() const {return re;}
double Complex::img() const {return im;}

Complex& Complex::operator+=(const Complex& other)
{
    re += other.re;
    im += other.im;
    return *this;
}

bool Complex::operator==(const Complex& other) const
{
    return re == other.re && im == other.im;
}

Complex operator+(Complex lhs, const Complex& rhs)
{
    lhs += rhs;
    return lhs;
}


std::ostream& operator<<(std::ostream& os, const Complex& c)
{
    os << c.re;
    if (c.im >= 0) os << " + " << c.im << "i";
    else os << " - " << (-c.im) << "i";
    return os;
}
