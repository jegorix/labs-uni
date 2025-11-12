#include "../include/Shkolnik.h"
#include <iomanip>

int Shkolnik::getGrade() {
    return grade;
}

void Shkolnik::setGrade(int new_grade) {
    grade = new_grade;
}

Shkolnik& Shkolnik::operator=(const Shkolnik& object) {
    Uchaschiysya::operator=(object);
    grade = object.grade;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Shkolnik& object) {
    os << static_cast<const Uchaschiysya&>(object);
    os << " Класс: " << object.grade << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, Shkolnik& object) {
    is >> static_cast<Uchaschiysya&>(object);
    std::cout << " Введите класс " << "\"" << object.name << "\"" << ": ";
    is >> object.grade;
    return is;
}

bool Shkolnik::operator==(const Shkolnik& other) const {
    // Поиск по имени, возрасту и классу
    return (static_cast<const Uchaschiysya&>(*this) == static_cast<const Uchaschiysya&>(other) 
            && grade == other.grade);
}

void Shkolnik::showMenu() {
    const int width = 60;
    Uchaschiysya::showMenu();
    std::cout << " |  6. Показать класс" << std::setw(width - 21) << " " << "|\n";
    std::cout << " |  7. Изменить класс" << std::setw(width - 21) << " " << "|\n";
    std::cout << " |  0. Выход" << std::setw(width - 12) << " " << "|\n";
    std::cout << " +" << std::setfill('=') << std::setw(width - 1) << "+" << "\n";
    std::cout << " Ваш выбор: ";
}

void Shkolnik::printHeader() const {
    std::cout << " | " << std::left << std::setw(20) << "Имя";
    std::cout << " | " << std::left << std::setw(20) << "Возраст";
    std::cout << "| " << std::left << std::setw(20) << "Класс" << "|" << std::endl;
}

void Shkolnik::printTable() const {
    std::cout << " | " << std::left << std::setw(20) << this->name;
    std::cout << "| " << std::left << std::setw(15) << this->age;
    std::cout << "| " << std::left << std::setw(15) << this->grade << "|" << std::endl;
}
