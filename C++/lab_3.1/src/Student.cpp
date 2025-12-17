#include "../include/Student.h"
#include <iomanip>

int Student::getCourse() {
    return course;
}

void Student::setCourse(int new_course) {
    course = new_course;
}

Student& Student::operator=(const Student& object) {
    Uchaschiysya::operator=(object); // копируем часть базового класса
    course = object.course; // копируем часть производного класса
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Student& object) {
    static bool headerPrinted = false;

    if (!headerPrinted) {
        char oldFill = os.fill(' ');
        os << " | " << std::left << std::setw(20) << "Имя";
        os << "| " << std::left << std::setw(10) << "Возраст";
        os << "| " << std::left << std::setw(10) << "Курс" << "|" << std::endl;
        os.fill(oldFill);
        headerPrinted = true;
    }

    char oldFill = os.fill(' ');
    os << static_cast<const Uchaschiysya&>(object); // для вывода полей базового класса, т.к там реализована перегрузка вывода
    os << "| " << std::left << std::setw(10) << object.course << "|" << std::endl;
    os.fill(oldFill);
    return os;
}

std::istream& operator>>(std::istream& is, Student& object) {
    is >> static_cast<Uchaschiysya&>(object); // для ввода полей базового класса, т.к там реализована перегрузка ввода
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