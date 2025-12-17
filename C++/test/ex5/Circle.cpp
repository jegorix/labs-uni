#include "Circle.h"
#include <cmath>

Circle::Circle(const std::string& name, double radius)
    : Shape(name), radius(radius)
    {
        if(radius <= 0)
        {
            throw std::invalid_argument("Radius must be positive");
        }
    }


double Circle::getArea() const 
{
    return M_PI * radius * radius;
}

void Circle::printInfo() const 
{
    std::cout << "Circle: " << name << "\n"
    << "Radius: " << radius << "\n"
    << "Area: " << getArea() << std::endl;

}

void Circle::scale(double factor)
{
    if(factor <= 0)
    {
        throw std::invalid_argument("Scale must be positive");
    }
    radius *= factor;
}

double Circle::getRadius() const 
{
    return radius;
}

void Circle::setRadius(double newRadius)
{
    if (newRadius <= 0)
    {
        throw std::invalid_argument("Radius must be positive");
    }
    radius = newRadius;
}

