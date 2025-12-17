#include "../include/Shkolnik.h"
#include "../include/InputUtils.h"
#include <iomanip>

int Shkolnik::getGrade() {
    return grade;
}

int Shkolnik::getGrade() const {
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
    // Сначала вводим общие данные учащегося (ФИО и возраст) с проверкой
    is >> static_cast<Uchaschiysya&>(object);

    // Затем запрашиваем класс (1..11, например) с проверкой диапазона
    std::string prompt = "Класс \"" + std::string(object.name) + "\" (1..11): ";
    object.grade = readInt(is, prompt, 1, 11);
    return is;
}

bool Shkolnik::operator==(const Shkolnik& other) const {
    // Поиск по ФИО, возрасту и классу
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
    std::cout << "| " << std::left << std::setw(NAME_COL_WIDTH) << "ФИО"
              << " | " << std::left << std::setw(AGE_COL_WIDTH) << "Возраст"
              << " | " << std::left << std::setw(EXTRA_COL_WIDTH) << "Класс"
              << " |" << std::endl;
}

void Shkolnik::printTable() const {
    std::cout << "| " << std::left << std::setw(NAME_COL_WIDTH) << truncateName(this->name)
              << " | " << std::left << std::setw(AGE_COL_WIDTH) << this->age
              << " | " << std::left << std::setw(EXTRA_COL_WIDTH) << this->grade
              << " |" << std::endl;
}
