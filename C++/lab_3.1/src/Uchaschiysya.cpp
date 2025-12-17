#include "../include/Uchaschiysya.h"
#include <iomanip>
#include <limits>

char* Uchaschiysya::getName() {
    return name;
}

int Uchaschiysya::getAge() {
    return age;
}

void Uchaschiysya::setName(char* new_name) {
    strcpy(name, new_name);
}

void Uchaschiysya::setAge(int new_age) {
    age = new_age;
}

Uchaschiysya& Uchaschiysya::operator=(const Uchaschiysya& object) {
    strcpy(name, object.name);
    age = object.age;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Uchaschiysya& object) {
    os << " | " << std::left << std::setw(20)
       << ((object.name[0] != '\0') ? object.name : "неопределенно");
    os << "| " << std::left << std::setw(10) << object.age;
    return os; // завершающую черту и перевод строки добавляют производные классы
}

std::istream& operator>>(std::istream& is, Uchaschiysya& object) {
    // очищаем буфер от возможного оставшегося символа новой строки
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Введите имя (до 31 символа): ";
    is.getline(object.name, 32);
    std::cout << "Введите возраст: ";
    is >> object.age;
    return is;
}

void Uchaschiysya::showMenu() {
    const int width = 60;
    std::cout << " +" << std::setfill('=') << std::setw(width - 1) << "+" << std::endl;
    std::cout << " |  1. Показать всю информацию" << std::setw(width - 31) << " " << "|" << std::endl;
    std::cout << " |  2. Показать список" << std::setw(width - 23) << " " << "|" << std::endl;
    std::cout << " |  3. Показать имя" << std::setw(width - 20) << " " << "|" << std::endl;
    std::cout << " |  4. Изменить имя" << std::setw(width - 19) << " " << "|" << std::endl;
    std::cout << " |  5. Показать возраст" << std::setw(width - 24) << " " << "|" << std::endl;
    std::cout << " |  6. Изменить возраст" << std::setw(width - 23) << " " << "|" << std::endl;
}