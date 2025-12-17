#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>
#include <string>
#include <cmath>

class Shape
{
    protected:
        std::string name;

    public:
        Shape(const std::string& name);

        virtual ~Shape() = default;

        virtual double getArea() const = 0;
        virtual void printInfo() const;
        virtual void scale(double factor);

        std::string getName() const;
        void setName(const std::string& newName);
    
};


#endif
