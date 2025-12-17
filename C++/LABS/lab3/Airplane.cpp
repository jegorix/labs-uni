#include "Airplane.h"


int Airplane::getMaxAltitude()
{
    return max_altitude;
}


void Airplane::setMaxAltitude(int new_max_altitude)
{
    max_altitude = new_max_altitude;
}


Airplane& Airplane::operator = (const Airplane& object)
{
    CargoCarrier::operator = (object);
    max_altitude = object.max_altitude;
    return *this;
}


std::ostream& operator << (std::ostream& os, const Airplane& object)
{
    os << static_cast<const CargoCarrier&>(object);
    os << " Макс. высота: " << object.max_altitude << " км" << std::endl;
    return os;
}


std::istream& operator >> (std::istream& is, Airplane& object)
{
    is >> static_cast<CargoCarrier&>(object);
    std::cout << " Введите макс. высоту полета " << "\"" << object.name << "\"" << "(км): ";
    is >> object.max_altitude;

    return is;
}


void Airplane::showMenu()
{
    const int width = 60;

    CargoCarrier::showMenu();

    std::cout << " |  9. Показать макс. высоту полёта";                                                                                                   // отрисовка 8 пункта
    std::cout << std::setw(width - 35) << " " << "|\n";

    std::cout << " |  10. Изменить макс. высоту полёта";                                                                                                   // отрисовка 9 пункта
    std::cout << std::setw(width - 36) << " " << "|\n";

    std::cout << " |  0. Выход";                                                                                                                          // отрисовка пункта выхода
    std::cout << std::setw(width - 12) << " " << "|\n";

    std::cout << " +" << std::setfill('=') << std::setw(width - 1) << "+" << "\n";																		 // отрисовка нижней границы меню
    std::cout << " Ваш выбор: ";
}