#include "../include/Uchaschiysya.h"  // Adjust path if needed
#include "../include/InputUtils.h"

char* Uchaschiysya::getName() {
    return name;
}

const char* Uchaschiysya::getName() const {
    return name;
}

int Uchaschiysya::getAge() {
    return age;
}

int Uchaschiysya::getAge() const {
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
    os << "Имя: " << ((object.name[0] != '\0') ? object.name : "неопределенно") << std::endl;
    os << "Возраст: " << object.age << " лет" << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, Uchaschiysya& object) {
    // Подробно подсказываем пользователю формат ввода
    std::cout << "Введите данные учащегося.\n";
    std::cout << "Фамилия: только буквы (латиница или кириллица в зависимости от задания).\n";
    std::cout << "Возраст: целое число от 1 до 120.\n";

    // Ввод фамилии с проверкой
    readName(is, object.name, 32,
             "Введите фамилию (до 31 символа, только буквы): ",
             false /* false -> ожидаем латиницу, true -> только 'русские' символы */);

    // Ввод возраста с проверкой
    object.age = readInt(is,
                         "Введите возраст (1..120): ",
                         1,
                         120);
    return is;
}

bool Uchaschiysya::operator==(const Uchaschiysya& other) const {
    // Поиск по имени и возрасту
    return (strcmp(name, other.name) == 0 && age == other.age);
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

void Uchaschiysya::printHeader() const {
    std::cout << " | " << std::left << std::setw(20) << "Имя";
    std::cout << "| " << std::left << std::setw(15) << "Возраст" << "|" << std::endl;
}

void Uchaschiysya::printTable() const {
    std::cout << " | " << std::left << std::setw(20) << name;
    std::cout << "| " << std::left << std::setw(15) << age << "|" << std::endl;
}
