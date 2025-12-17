#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <iostream>

class Device {
    protected:
        std::string name;
        int year;

    public:
        Device();
        Device(std::string name, int year);

        virtual ~Device();

        virtual void showInfo() const;

        friend std::ostream& operator<<(std::ostream& os, const Device& d);
};

#endif