#include "../include/Human.hpp"
#include "../../exceptions/include/InputHandler.hpp"
using namespace std;
Human::Human() : birthday() {}
Human::Human(const string& first, const string& last, const string& middle, const Date& birth)
    : firstName(first), lastName(last), middleName(middle), birthday(birth) {}
Human::~Human() {}
Human& Human::operator=(const Human& other) {
    if (this != &other) {
        this->firstName = other.firstName;
        this->lastName = other.lastName;
        this->middleName = other.middleName;
        this->birthday = other.birthday;
    }
    return *this;
}
bool Human::operator==(const Human& other) const {
    if (currentSearchMode == FULL_MATCH) {
        return firstName == other.firstName &&
               lastName == other.lastName &&
               middleName == other.middleName &&
               birthday == other.birthday;
    } else if (currentSearchMode == LAST_NAME) {
        return lastName == other.lastName;
    } else if (currentSearchMode == FIRST_NAME) {
        return firstName == other.firstName;
    } else if (currentSearchMode == MIDDLE_NAME) {
        return middleName == other.middleName;
    } else if (currentSearchMode == BIRTH_YEAR) {
        return birthday == other.birthday;
    }
    return false;
}
bool Human::operator<(const Human& other) const {
    if (currentSearchMode == LAST_NAME) {
        return this->lastName < other.lastName;
    } else if (currentSearchMode == FIRST_NAME) {
        return this->firstName < other.firstName;
    } else if (currentSearchMode == MIDDLE_NAME) {
        return this->middleName < other.middleName;
    } else if (currentSearchMode == BIRTH_YEAR) {
        return this->birthday < other.birthday;
    }
    return false;
}
ostream& operator<<(ostream& os, const Human& member) {
    os << member.firstName << " " << member.lastName << " " << member.middleName << " " << member.birthday;
    return os;
}
istream& operator>>(istream& is, Human& member) {
    member.firstName = safeGetLine(is, Language::ENGLISH, "Enter first name (English only): ");
    member.lastName = safeGetLine(is, Language::ENGLISH, "Enter last name (English only): ");
    member.middleName = safeGetLine(is, Language::ENGLISH, "Enter middle name (English only): ");
    member.birthday = safeInputDate(is, "DD/MM/YYYY", "Enter birthday (DD/MM/YYYY): ");
    return is;
}
string Human::getFirstName() const { return this->firstName; }
string Human::getLastName() const { return this->lastName; }
string Human::getMiddleName() const { return this->middleName; }
Date Human::getBirthday() const { return this->birthday; }
void Human::setFirstName(const string& first) { this->firstName = first; }
void Human::setLastName(const string& last) { this->lastName = last; }
void Human::setMiddleName(const string& middle) { this->middleName = middle; }
void Human::setBirthday(const Date& birth) { this->birthday = birth; }
void Human::setSearchMode(SearchMode mode) { currentSearchMode = mode; }
SearchMode Human::currentSearchMode = FULL_MATCH;
void Human::updateField(int fieldChioce) {
    string str;
    Date date;
    switch(fieldChioce) {
        case 1:
            str = safeGetLine(cin, Language::ENGLISH, "New first name (English only): ");
            setFirstName(str);
            break;
        case 2:
            str = safeGetLine(cin, Language::ENGLISH, "New last name (English only): ");
            setLastName(str);
            break;
        case 3:
            str = safeGetLine(cin, Language::ENGLISH, "New middle name (English only): ");
            setMiddleName(str);
            break;
        case 4:
            date = safeInputDate(cin, "DD/MM/YYYY", "New birthday (DD/MM/YYYY): ");
            setBirthday(date);
            break;
    }
}
void Human::printHeader() const {}
void Human::printTable() const {}