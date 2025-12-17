#include "Money.h"
#include <iostream>

int main()
{
    Money m1(123, 45);  // 123.45
    Money m2(50, 80);   // 50.80
    Money m3 = m1 + m2; // 174.25

    m1.print();
    m2.print();
    m3.print();

    return 0;
}