#include "../include/Student.h"
#include "../include/InputUtils.h"
#include <iomanip>

int Student::getCourse() {
    return course;
}

int Student::getCourse() const {
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
    // Сначала вводим общие данные учащегося (ФИО и возраст) с проверкой
    is >> static_cast<Uchaschiysya&>(object);

    // Затем запрашиваем курс с проверкой диапазона
    std::string prompt = "Курс \"" + std::string(object.name) + "\" (1..6): ";
    object.course = readInt(is, prompt, 1, 6);
    return is;
}

bool Student::operator==(const Student& other) const {
    // Поиск по ФИО, возрасту и курсу
    return (static_cast<const Uchaschiysya&>(*this) == static_cast<const Uchaschiysya&>(other) 
            && course == other.course);
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
    std::cout << "| " << std::left << std::setw(NAME_COL_WIDTH) << "ФИО"
              << " | " << std::left << std::setw(AGE_COL_WIDTH) << "Возраст"
              << " | " << std::left << std::setw(EXTRA_COL_WIDTH) << "Курс"
              << " |" << std::endl;
}

void Student::printTable() const {
    std::cout << "| " << std::left << std::setw(NAME_COL_WIDTH) << truncateName(this->name)
              << " | " << std::left << std::setw(AGE_COL_WIDTH) << this->age
              << " | " << std::left << std::setw(EXTRA_COL_WIDTH) << this->course
              << " |" << std::endl;
}
