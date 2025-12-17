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
    static bool headerPrinted = false;
    const int nameWidth  = 20;
    const int ageWidth   = 10;
    const int gradeWidth = 10;

    char oldFill = os.fill(' ');

    // Печатаем заголовок один раз
    if (!headerPrinted) {
        os << "| " << std::left << std::setw(nameWidth)  << "Имя"
           << " | " << std::left << std::setw(ageWidth)   << "Возраст"
           << " | " << std::left << std::setw(gradeWidth) << "Класс"
           << " |" << std::endl;
        headerPrinted = true;
    }

    // Строка таблицы для конкретного объекта
    os << "| " << std::left << std::setw(nameWidth)
       << ((object.name[0] != '\0') ? object.name : "неопределенно");
    os << " | " << std::left << std::setw(ageWidth) << object.age;
    os << " | " << std::left << std::setw(gradeWidth) << object.grade
       << " |" << std::endl;

    os.fill(oldFill);
    return os;
}

std::istream& operator>>(std::istream& is, Shkolnik& object) {
    is >> static_cast<Uchaschiysya&>(object);
    std::cout << " Введите класс " << "\"" << object.name << "\"" << ": ";
    is >> object.grade;
    return is;
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