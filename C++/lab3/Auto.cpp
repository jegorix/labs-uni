#include "Auto.h"


int Auto::getLoadCapacity()
{
    return load_capacity;
}


void Auto::setLoadCapacity(int new_load_capacity)
{
    load_capacity = new_load_capacity;
}


Auto& Auto::operator = (const Auto& object)
{
    CargoCarrier::operator = (object);
    load_capacity = object.load_capacity;
    return *this;
}


std::ostream& operator << (std::ostream& os, const Auto& object)
{
    os << static_cast<const CargoCarrier&>(object);
    os << " Грузоподъёмность: " << object.load_capacity << " кг" << std::endl;

    return os;
}


std::istream& operator >> (std::istream& is, Auto& object)
{
    is >> static_cast<CargoCarrier&>(object);
    std::cout << " Введите грузоподъёмность " << "\"" << object.name << "\"" << "(кг): ";
    is >> object.load_capacity;

    return is;
}


void Auto::showMenu()
{
    const int width = 60;

    CargoCarrier::showMenu();

    std::cout << " |  9. Показать грузоподъёмность";
    std::cout << std::setw(width - 33) << " " << "|\n";

    std::cout << " |  10. Изменить грузоподъёмность";
    std::cout << std::setw(width - 33) << " " << "|\n";

    std::cout << " |  0. Выход";
    std::cout << std::setw(width - 12) << " " << "|\n";

    // Нижняя граница меню
    std::cout << " +" << std::setfill('=') << std::setw(width - 1) << "+" << "\n";
    std::cout << " Ваш выбор: ";
}
