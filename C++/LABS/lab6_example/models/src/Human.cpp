#include "../include/Human.hpp"
#include "../../exceptions/include/InputHandler.hpp"
#include "../../exceptions/include/FileException.hpp"
#include <sstream>

using namespace std;

SearchMode Human::currentSearchMode = FULL_MATCH;

Human::Human() : birthday() {}

Human::Human(const string& first, const string& last, const string& middle, const Date& birth)
    : firstName(first), lastName(last), middleName(middle), birthday(birth) {}

Human::~Human() {}

Human::Human(const Human& other)
    : firstName(other.firstName),
      lastName(other.lastName),
      middleName(other.middleName),
      birthday(other.birthday) {}

Human& Human::operator=(const Human& other) {
    if (this != &other) {
        firstName = other.firstName;
        lastName = other.lastName;
        middleName = other.middleName;
        birthday = other.birthday;
    }
    return *this;
}

string Human::getFirstName() const { return firstName; }
string Human::getLastName() const { return lastName; }
string Human::getMiddleName() const { return middleName; }
Date Human::getBirthday() const { return birthday; }

void Human::setFirstName(const string& first) { firstName = first; }
void Human::setLastName(const string& last) { lastName = last; }
void Human::setMiddleName(const string& middle) { middleName = middle; }
void Human::setBirthday(const Date& birth) { birthday = birth; }

void Human::setSearchMode(SearchMode mode) { currentSearchMode = mode; }
SearchMode Human::getSearchMode() { return currentSearchMode; }

bool Human::operator==(const Human& other) const {
    switch (currentSearchMode) {
        case FULL_MATCH:
            return firstName == other.firstName &&
                   lastName == other.lastName &&
                   middleName == other.middleName &&
                   birthday == other.birthday;
        case LAST_NAME:
            return lastName == other.lastName;
        case FIRST_NAME:
            return firstName == other.firstName;
        case MIDDLE_NAME:
            return middleName == other.middleName;
        case BIRTH_YEAR:
            return birthday == other.birthday;
        default:
            return false;
    }
}

bool Human::operator<(const Human& other) const {
    switch (currentSearchMode) {
        case LAST_NAME:
            return lastName < other.lastName;
        case FIRST_NAME:
            return firstName < other.firstName;
        case MIDDLE_NAME:
            return middleName < other.middleName;
        case BIRTH_YEAR:
            return birthday < other.birthday;
        case FULL_MATCH:
        default:
            if (lastName != other.lastName) return lastName < other.lastName;
            if (firstName != other.firstName) return firstName < other.firstName;
            if (middleName != other.middleName) return middleName < other.middleName;
            return birthday < other.birthday;
    }
}

ostream& operator<<(ostream& os, const Human& member) {
    os << member.lastName << " " << member.firstName << " " << member.middleName << " " << member.getBirthday().toString();
    return os;
}

istream& operator>>(istream& is, Human& member) {
    member.firstName = safeGetLine(is, Language::ENGLISH, "Enter first name (English only): ");
    member.lastName = safeGetLine(is, Language::ENGLISH, "Enter last name (English only): ");
    member.middleName = safeGetLine(is, Language::ENGLISH, "Enter middle name (English only): ");
    member.birthday = safeInputDate(is, "DD/MM/YYYY", "Enter birthday (DD/MM/YYYY): ");
    return is;
}

void Human::printHeader() const {}

void Human::printTable() const {}

void Human::updateField(int fieldChoice) {
    string str;
    Date date;
    switch (fieldChoice) {
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
        default:
            break;
    }
}

namespace {
    void writeInt(ostream& os, int value) {
        os.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }

    int readInt(istream& is) {
        int value = 0;
        if (!is.read(reinterpret_cast<char*>(&value), sizeof(value))) {
            throw FileException(70, "Error reading integer from binary file");
        }
        return value;
    }

    void writeString(ostream& os, const string& s) {
        int len = static_cast<int>(s.size());
        writeInt(os, len);
        if (len > 0) {
            os.write(s.data(), len);
        }
    }

    string readString(istream& is) {
        int len = readInt(is);
        if (len < 0) {
            throw FileException(71, "Negative string length in binary file");
        }
        string s;
        s.resize(len);
        if (len > 0) {
            if (!is.read(&s[0], len)) {
                throw FileException(72, "Error reading string data from binary file");
            }
        }
        return s;
    }
}

void Human::saveTextRecord(ostream& os) const {
    os << firstName << ';'
       << lastName << ';'
       << middleName << ';'
       << birthday.toString();
}

Human* Human::readTextRecord(istream& is) {
    string line;
    if (!std::getline(is, line)) {
        return nullptr;
    }
    if (line.empty()) {
        return nullptr;
    }

    istringstream iss(line);
    string first, last, middle, dateStr;

    if (!std::getline(iss, first, ';') ||
        !std::getline(iss, last, ';') ||
        !std::getline(iss, middle, ';') ||
        !std::getline(iss, dateStr, ';')) {
        throw FileException(73, "Invalid Human text record format");
    }

    Date birth;
    {
        istringstream ds(dateStr);
        ds >> birth;
    }

    Human* h = new Human(first, last, middle, birth);
    return h;
}

void Human::saveBinaryRecord(ostream& os) const {
    writeString(os, firstName);
    writeString(os, lastName);
    writeString(os, middleName);
    writeString(os, birthday.toString());
}

Human* Human::readBinaryRecord(istream& is) {
    if (is.peek() == EOF) {
        return nullptr;
    }

    string first = readString(is);
    string last = readString(is);
    string middle = readString(is);
    string dateStr = readString(is);

    Date birth;
    {
        istringstream ds(dateStr);
        ds >> birth;
    }

    Human* h = new Human(first, last, middle, birth);
    return h;
}
