#include <iostream>
#include "complex.h"

int main()
{
    Complex a(1.0, 2.0);
    Complex b(3.0, -0.5);

    Complex c = a + b;
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "a + b = " << c << std::endl;

    a += b;
    std::cout << "a after += b: " << a << "\n";

    std::cout << std::boolalpha << "a == c ?" << (a == c) << std::endl;

    return 0;

}