#include <iostream>
#include "include/print.h"



struct Point {
    int x, y;
};


std::ostream& operator<<(std::ostream& os, const Point& p)
{
    return os << "(" << p.x << ", " << p.y << ")";
}

int main() {

//    int a = 5;
//    int& b = a;
//    int* c = &b;
//    print("hello world =",a, "and b =", b, "c =", *c);

    Point p{10, 20};
//    print("Point:", p);
py::printf("Point {}", p);

//py::printf("Hello {} and {}", a, "world");


    return 0;
}