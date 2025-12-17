#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>

class Complex
{
    private:
        double re;
        double im;

    public:
        Complex(double r = 0.0, double i = 0.0);

        double real() const;
        double img() const;

        Complex& operator+=(const Complex& other);
        bool operator==(const Complex& other) const;

        friend Complex operator+(Complex lhs, const Complex& rhs);
        friend std::ostream& operator<<(std::ostream& os, const Complex& c);

};

#endif
