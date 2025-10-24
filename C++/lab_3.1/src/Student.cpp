#include "../include/Student.h"
#include <iomanip>

int Student::getCourse() {
    return course;
}

void Student::setCourse(int new_course) {
    course = new_course;
}

Student& Student::operator=(const Student& object) {
    Uchaschiysya::operator=(object);
    course = object.course;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Student& object) {
    os << static_cast<const Uchaschiysya&>(object);
    os << " Курс: " << object.course << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, Student& object) {
    is >> static_cast<Uchaschiysya&>(object);
    std::cout << " Введите курс " << "\"" << object.name << "\"" << ": ";
    is >> object.course;
    return is;
}

void Student::showMenu() {
    const int width = 60;
    Uchaschiysya::showMenu();
    std::cout << " |  6. Показать курс" << std::setw(width - 20) << " " << "|\n";
    std::cout << " |  7. Изменить курс" << std::setw(width - 19) << " " << "|\n";
    std::cout << " |  0. Выход" << std::setw(width - 12) << " " << "|\n";
    std::cout << " +" << std::setfill('=') << std::setw(width - 1) << "+" << "\n";
    std::cout << " Ваш выбор: ";
}

void Student::printHeader() const {
    std::cout << " | " << std::left << std::setw(20) << "Имя";
    std::cout << "| " << std::left << std::setw(15) << "Возраст";
    std::cout << "| " << std::left << std::setw(15) << "Курс" << "|" << std::endl;
}

void Student::printTable() const {
    std::cout << " | " << std::left << std::setw(20) << this->name;
    std::cout << "| " << std::left << std::setw(15) << this->age;
    std::cout << "| " << std::left << std::setw(15) << this->course << "|" << std::endl;
}