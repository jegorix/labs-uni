#include "../include/Shkolnik.h"
#include "../include/InputUtils.h"
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <cstring>

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
    // Сначала вводим общие данные учащегося (фамилия и возраст) с проверкой
    is >> static_cast<Uchaschiysya&>(object);

    // Затем запрашиваем класс (1..11, например) с проверкой диапазона
    std::string prompt = " Введите класс \"" + std::string(object.name) + "\" (1..11): ";
    object.grade = readInt(is, prompt, 1, 11);
    return is;
}

bool Shkolnik::operator==(const Shkolnik& other) const {
    // Поиск по имени, возрасту и классу
    return (static_cast<const Uchaschiysya&>(*this) == static_cast<const Uchaschiysya&>(other) 
            && grade == other.grade);
}

std::string Shkolnik::toTextRecord() const {
    std::ostringstream oss;
    oss << this->name << ";" << this->age << ";" << this->grade;
    return oss.str();
}

Shkolnik Shkolnik::fromTextRecord(const std::string& line) {
    std::stringstream ss(line);
    std::string token;
    Shkolnik obj;

    if (!std::getline(ss, token, ';')) {
        throw std::runtime_error("Некорректная строка (имя)");
    }
    char buffer[32];
    std::strncpy(buffer, token.c_str(), 31);
    buffer[31] = '\0';
    obj.setName(buffer);

    if (!std::getline(ss, token, ';')) {
        throw std::runtime_error("Некорректная строка (возраст)");
    }
    obj.setAge(std::stoi(token));

    if (!std::getline(ss, token, ';')) {
        throw std::runtime_error("Некорректная строка (класс)");
    }
    obj.setGrade(std::stoi(token));

    return obj;
}

Shkolnik::BinaryRecord Shkolnik::toBinaryRecord() const {
    BinaryRecord rec{};
    std::strncpy(rec.name, this->name, 31);
    rec.name[31] = '\0';
    rec.age = this->age;
    rec.grade = this->grade;
    return rec;
}

Shkolnik Shkolnik::fromBinaryRecord(const Shkolnik::BinaryRecord& record) {
    Shkolnik obj;
    char buffer[32];
    std::strncpy(buffer, record.name, 31);
    buffer[31] = '\0';
    obj.setName(buffer);
    obj.setAge(record.age);
    obj.setGrade(record.grade);
    return obj;
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
