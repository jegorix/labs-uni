#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"
#include <string.h>
#include <iostream>


class Circle : public Shape
{
    protected:
        double radius;

    public:
        Circle(const std::string& name, double radius);

        double getArea() const override;
        void printInfo() const override;
        void scale(double factor) override;

        double getRadius() const;
        void setRadius(double newRadius); 

};

#endif