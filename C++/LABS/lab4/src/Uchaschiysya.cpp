#include "../include/Uchaschiysya.h"  // Adjust path if needed
#include "../include/InputUtils.h"

#include <vector>

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
    os << "ФИО: " << ((object.name[0] != '\0') ? object.name : "неопределенно") << std::endl;
    os << "Возраст: " << object.age << " лет" << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, Uchaschiysya& object) {
    // Ввод без лишнего шума: сразу показываем короткие подсказки в самих промптах.
    std::string prompt = useRussianNames()
                         ? "\nФИО (кириллица, до 63 символов, через пробел): "
                         : "\nФИО (латиница, до 63 символов, через пробел): ";
    readName(is, object.name, Uchaschiysya::NAME_CAP,
             prompt,
             useRussianNames() /* false -> латиница, true -> кириллица */);

    object.age = readInt(is,
                         "Возраст (1..120): ",
                         1,
                         120);
    return is;
}

bool Uchaschiysya::operator==(const Uchaschiysya& other) const {
    // Поиск по ФИО и возрасту
    return (strcmp(name, other.name) == 0 && age == other.age);
}

static std::vector<std::size_t> utf8Offsets(const std::string& s) {
    std::vector<std::size_t> offsets;
    for (std::size_t i = 0; i < s.size();) {
        unsigned char c = static_cast<unsigned char>(s[i]);
        std::size_t len = 1;
        if (c < 0x80) len = 1;
        else if ((c >> 5) == 0x6) len = 2;
        else if ((c >> 4) == 0xE) len = 3;
        else if ((c >> 3) == 0x1E) len = 4;
        else break;
        if (i + len > s.size()) break;
        offsets.push_back(i);
        i += len;
    }
    return offsets;
}

std::string Uchaschiysya::truncateName(const char* src) {
    if (src == nullptr) return "";
    std::string s(src);
    auto offsets = utf8Offsets(s);
    if (offsets.size() <= static_cast<std::size_t>(NAME_COL_WIDTH)) {
        return s;
    }
    // Оставляем первые NAME_COL_WIDTH-3 символа и добавляем "..."
    std::size_t keep = (NAME_COL_WIDTH > 3) ? static_cast<std::size_t>(NAME_COL_WIDTH - 3) : 0;
    if (keep >= offsets.size()) keep = offsets.size();
    std::size_t cutPos = offsets[keep];
    return s.substr(0, cutPos) + "...";
}

void Uchaschiysya::showMenu() {
    const int width = 60;
    std::cout << " +" << std::setfill('=') << std::setw(width - 1) << "+" << std::endl;
    std::cout << " |  1. Показать всю информацию" << std::setw(width - 31) << " " << "|" << std::endl;
    std::cout << " |  2. Показать список" << std::setw(width - 23) << " " << "|" << std::endl;
    std::cout << " |  3. Показать ФИО" << std::setw(width - 21) << " " << "|" << std::endl;
    std::cout << " |  4. Изменить ФИО" << std::setw(width - 20) << " " << "|" << std::endl;
    std::cout << " |  5. Показать возраст" << std::setw(width - 24) << " " << "|" << std::endl;
    std::cout << " |  6. Изменить возраст" << std::setw(width - 23) << " " << "|" << std::endl;
}

void Uchaschiysya::printHeader() const {
    std::cout << "| " << std::left << std::setw(NAME_COL_WIDTH) << "ФИО"
              << " | " << std::left << std::setw(AGE_COL_WIDTH) << "Возраст"
              << " |" << std::endl;
}

void Uchaschiysya::printTable() const {
    std::cout << "| " << std::left << std::setw(NAME_COL_WIDTH) << truncateName(name)
              << " | " << std::left << std::setw(AGE_COL_WIDTH) << age
              << " |" << std::endl;
}
