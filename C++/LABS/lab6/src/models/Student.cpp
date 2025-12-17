#include "../../include/models/Student.h"
#include "../../include/utils/InputUtils.h"
#include <iomanip>
#include <sstream>

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

void Student::saveTextRecord(std::ostream& os) {
    os << this->name << ";" << this->age << ";" << this->course;
}

Student* Student::readTextRecord(std::istream& is) {
    std::string line;
    if (!std::getline(is, line)) return nullptr;
    if (line.empty()) return nullptr;
    std::stringstream ss(line);
    std::string part;
    Student* obj = new Student();

    if (!std::getline(ss, part, ';')) { delete obj; return nullptr; }
    std::strncpy(obj->name, part.c_str(), NAME_CAP - 1); obj->name[NAME_CAP - 1] = '\0';

    if (!std::getline(ss, part, ';')) { delete obj; return nullptr; }
    obj->age = std::stoi(part);

    if (!std::getline(ss, part, ';')) { delete obj; return nullptr; }
    obj->course = std::stoi(part);

    return obj;
}

void Student::saveBinaryRecord(std::ostream& os) {
    BinaryRecord rec{};
    std::strncpy(rec.name, this->name, NAME_CAP - 1);
    rec.name[NAME_CAP - 1] = '\0';
    rec.age = this->age;
    rec.course = this->course;
    os.write(reinterpret_cast<const char*>(&rec), sizeof(rec));
}

Student* Student::readBinaryRecord(std::istream& is) {
    BinaryRecord rec{};
    if (!is.read(reinterpret_cast<char*>(&rec), sizeof(rec))) {
        return nullptr;
    }
    Student* obj = new Student();
    obj->setName(rec.name);
    obj->setAge(rec.age);
    obj->setCourse(rec.course);
    return obj;
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
