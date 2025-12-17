#include "CargoCarrier.h"


char* CargoCarrier::getName()
{
    return name;
}

int CargoCarrier::getSpeed()
{
    return speed;
}

int CargoCarrier::getStake()
{
    return stake;
}



void CargoCarrier::setName(char *new_name)
{
    strcpy(name, new_name);
}

void CargoCarrier::setSpeed(int new_speed)
{
    speed = new_speed;
}

void CargoCarrier::setStake(int new_stake)
{
    stake = new_stake;
}


CargoCarrier& CargoCarrier::operator = (const CargoCarrier& other)
{
    if (this != &other)										// условия чтобы не копировать тот же объект
    {
        strcpy(name, other.name);
        speed = other.speed;
        stake = other.stake;
    }
    return *this;
}


std::ostream& operator << (std::ostream& os, const CargoCarrier& object)
{
    os << " Название: " << ((object.name) ? object.name : "неопределенно") << std::endl;
    os << " Скорость: " << object.speed << " км/ч" << std::endl;
    os << " Ставка: " << object.stake << " руб/км" << std::endl;

    return os;
}


std::istream& operator >> (std::istream& is, CargoCarrier& object)
{
    std::cout << " Введите название(только 64 символа): ";
    is.getline(object.name, 32);

    std::cout << " Введите скорость " << "\"" << object.name << "\"" << "(км/ч): ";
    is >> object.speed;

    std::cout << " Введите ставку " << "\"" << object.name << "\"" << "(руб/ч): ";
    is >> object.stake;

    return is;
}



void CargoCarrier::showMenu()
{
    const int width = 60;

    std::cout << "\n +" << std::setfill('=') << std::setw(width - 1) << "+" << "\n";

    // Заголовок по центру
    std::string title = "МЕНЮ КЛАССА";
    int padding = (width - 2 - (int)title.length()) / 2;
    std::cout << std::setfill(' ') << " |" << std::setw(padding) << " " << title << std::setw(width - 2 - padding - (int)title.length()) << " " << "|\n";

    std::cout << " +" << std::setfill('=') << std::setw(width - 1) << "+" << "\n";                                                                        // отрисовка рзделительной линии


    std::cout << std::setfill(' ') << " |  1. Показать всю информацию об объекте";                                                                        // отрисовка 1 пункта
    std::cout << std::setw(width - 41) << " " << "|\n";

    std::cout << " |  2. Определить время и стоимость перевозки";                                                                                                     // отрисовка 2 пункта
    std::cout << std::setw(width - 45) << " " << "|\n";

    std::cout << " |  3. Показать название";                                                                                                     // отрисовка 2 пункта
    std::cout << std::setw(width - 24) << " " << "|\n";

    std::cout << " |  4. Изменить название ";                                                                                                     // отрисовка 6 пункта
    std::cout << std::setw(width - 25) << " " << "|\n";

    std::cout << " |  5. Показать скорость";                                                                                                              // отрисовка 3 пункта
    std::cout << std::setw(width - 24) << " " << "|\n";

    std::cout << " |  6. Изменить скорость";                                                                                                              // отрисовка 7 пункта
    std::cout << std::setw(width - 24) << " " << "|\n";

    std::cout << " |  7. Показать ставку";                                                                                                                // отрисовка 4 пункта
    std::cout << std::setw(width - 22) << " " << "|\n";

    std::cout << " |  8. Изменить ставку";                                                                                                                // отрисовка 8 пункта
    std::cout << std::setw(width - 22) << " " << "|\n";
}


double CargoCarrier::calculatePrice(int distance)
{
    return distance / speed * stake;
}


double CargoCarrier::calculateTime(int distance)
{
    return distance / speed;
}