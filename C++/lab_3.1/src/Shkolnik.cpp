//
// Created by jegorix on 15.10.25.
//

#include "../include/Shkolnik.h"

int Shkolnik::getGrade()
{
    return grade;
}

void Shkolnik::setGrade(int new_grade)
{
    grade = new_grade;
}

Shkolnik& Shkolnik::operator = (const Shkolnik& object)
{
    Uchaschiysya::operator = (object);
    grade = object.grade;
    return *this;
}

std::ostream& operator << (std::ostream& os, const Shkolnik& object)
{
    os << static_cast<const Uchaschiysya&>(object);
    os << " Класс: " << object.grade << std::endl;
    return os;
}

std::istream& operator >> (std::istream& is, Shkolnik& object)
{
    is >> static_cast<Uchaschiysya&>(object);
    std::cout << " Введите класс " << "\"" << object.name << "\"" << ": ";
    is >> object.grade;

    return is;
}

void Shkolnik::showMenu()
{
    const int width = 60;

    Uchaschiysya::showMenu();

    std::cout << " |  6. Показать класс";
    std::cout << std::setw(width - 21) << " " << "|\n";

    std::cout << " |  7. Изменить класс";
    std::cout << std::setw(width - 21) << " " << "|\n";

    std::cout << " |  0. Выход";
    std::cout << std::setw(width - 12) << " " << "|\n";

    std::cout << " +" << std::setfill('=') << std::setw(width - 1) << "+" << "\n";
    std::cout << " Ваш выбор: ";
}
