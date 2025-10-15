#include "Train.h"



int Train::getWagonCount()
{
    return wagon_count;
}


void Train::setWagonCount(int new_wagon_count)
{
    wagon_count = new_wagon_count;
}


Train& Train::operator = (const Train& object)
{
    CargoCarrier::operator = (object);
    wagon_count = object.wagon_count;
    return *this;
}


std::ostream& operator << (std::ostream& os, const Train& object)
{
    os << static_cast<const CargoCarrier&>(object);
    os << " Количество вагонов: " << object.wagon_count << " шт" << std::endl;

    return os;
}


std::istream& operator >> (std::istream& is, Train& object)
{
    is >> static_cast<CargoCarrier&>(object);
    std::cout << " Введите количество вагонов " << "\"" << object.name << "\"" << "(шт): ";
    is >> object.wagon_count;

    return is;
}


void Train::showMenu()
{
    const int width = 60;

    CargoCarrier::showMenu();

    std::cout << " |  9. Показать количество вагонов";
    std::cout << std::setw(width - 34) << " " << "|\n";

    std::cout << " |  10. Изменить количество вагонов";
    std::cout << std::setw(width - 35) << " " << "|\n";

    std::cout << " |  0. Выход";
    std::cout << std::setw(width - 12) << " " << "|\n";

    // Нижняя граница меню
    std::cout << " +" << std::setfill('=') << std::setw(width - 1) << "+" << "\n";
    std::cout << " Ваш выбор: ";
}