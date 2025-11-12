#include "Device.h"

Device::Device(std::string name, int year) : name(name), year(year) {};

Device::~Device() {};

void Device::showInfo() const {
    std::cout << "Device: " << name << "\n" << "Year: " << year << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Device& d)
{
    d.showInfo();
} 
