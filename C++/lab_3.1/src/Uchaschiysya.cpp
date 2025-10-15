//
// Created by jegorix on 15.10.25.
//

#include "../include/Uchaschiysya.h"


char* Uchaschiysya::getName()
{
    return name;
}

int Uchaschiysya::getAge()
{
    return age;
}

void Uchaschiysya::setName(char *new_name)
{
    strcpy(name, new_name);
}

void Uchaschiysya::setAge(int new_age)
{
    age = new_age;
}

Uchaschiysya& Uchaschiysya::operator = (const Uchaschiysya& other)
{
    if (this != &other)
    {
        strcpy(name, other.name);
        age = other.age;
    }
    return *this;
}

std::ostream& operator << (std::ostream& os, const Uchaschiysya& object)
{
    os << " Название: " << ((object.name[0] != '\0') ? object.name : "неопределенно") << std::endl;
    os << " Возраст: " << object.age << " лет" << std::endl;
    return os;
}

std::istream& operator >> (std::istream& is, Uchaschiysya& object)
{
    std::cout << " Введите имя (до 31 символа): ";
    is.getline(object.name, 32);

    std::cout << " Введите возраст " << "\"" << object.name << "\"" << " (лет): ";
    is >> object.age;

    return is;
}

void Uchaschiysya::showMenu()
{
    const int width = 60;

    std::cout << "\n +" << std::setfill('=') << std::setw(width - 1) << "+" << "\n";

    std::string title = "МЕНЮ КЛАССА";
    int padding = (width - 58 - (int)title.length()) / 2;
    std::cout << std::setfill(' ') << " |" << std::setw(padding) << " " << title << std::setw(width - 2 - padding - (int)title.length()) << " " << "|\n";

    std::cout << " +" << std::setfill('=') << std::setw(width - 1) << "+" << "\n";

    std::cout << std::setfill(' ') << " |  1. Показать всю информацию об объекте";
    std::cout << std::setw(width - 41) << " " << "|\n";

    std::cout << " |  2. Показать имя";
    std::cout << std::setw(width - 19) << " " << "|\n";

    std::cout << " |  3. Изменить имя";
    std::cout << std::setw(width - 19) << " " << "|\n";

    std::cout << " |  4. Показать возраст";
    std::cout << std::setw(width - 21) << " " << "|\n";

    std::cout << " |  5. Изменить возраст";
    std::cout << std::setw(width - 21) << " " << "|\n";
}