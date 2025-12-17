#include "../include/Teacher.hpp"
#include "../../exceptions/include/InputHandler.hpp"
#include "../../exceptions/include/FileException.hpp"
#include <sstream>

using namespace std;

UniversityTeacher::UniversityTeacher() : Human(), scientificWorksCount(0) {}

UniversityTeacher::UniversityTeacher(const string& first, const string& last, const string& middle, const Date& birth,
                                     const string& pos, const string& degree, const string& spec)
    : Human(first, last, middle, birth),
      position(pos),
      academicDegree(degree),
      specialty(spec),
      scientificWorksCount(0) {}

UniversityTeacher::~UniversityTeacher() {}

UniversityTeacher::UniversityTeacher(const UniversityTeacher& other)
    : Human(other),
      position(other.position),
      academicDegree(other.academicDegree),
      specialty(other.specialty),
      scientificWorksCount(other.scientificWorksCount) {
    for (int i = 0; i < scientificWorksCount; ++i) {
        scientificWorks[i] = other.scientificWorks[i];
    }
}

UniversityTeacher& UniversityTeacher::operator=(const UniversityTeacher& other) {
    if (this != &other) {
        Human::operator=(other);
        position = other.position;
        academicDegree = other.academicDegree;
        specialty = other.specialty;
        scientificWorksCount = other.scientificWorksCount;
        for (int i = 0; i < scientificWorksCount; ++i) {
            scientificWorks[i] = other.scientificWorks[i];
        }
    }
    return *this;
}

string UniversityTeacher::getPosition() const { return position; }
string UniversityTeacher::getAcademicDegree() const { return academicDegree; }
string UniversityTeacher::getSpecialty() const { return specialty; }

string UniversityTeacher::getScientificWork(int index) const {
    if (index >= 0 && index < scientificWorksCount) {
        return scientificWorks[index];
    }
    return "";
}

int UniversityTeacher::getScientificWorksCount() const { return scientificWorksCount; }
int UniversityTeacher::getScientificWorksSize() const { return SCIENTIFIC_WORKS_SIZE; }

void UniversityTeacher::setPosition(const string& pos) { position = pos; }
void UniversityTeacher::setAcademicDegree(const string& degree) { academicDegree = degree; }
void UniversityTeacher::setSpecialty(const string& spec) { specialty = spec; }

void UniversityTeacher::setScientificWork(int index, const string& work) {
    if (index >= 0 && index < SCIENTIFIC_WORKS_SIZE) {
        if (index >= scientificWorksCount) {
            scientificWorksCount = index + 1;
        }
        scientificWorks[index] = work;
    }
}

void UniversityTeacher::addScientificWork(const string& work) {
    if (scientificWorksCount < SCIENTIFIC_WORKS_SIZE) {
        scientificWorks[scientificWorksCount++] = work;
    }
}

void UniversityTeacher::printHeader() const {
    cout << left << setw(15) << "Last Name"
         << left << setw(15) << "First Name"
         << left << setw(15) << "Middle Name"
         << left << setw(12) << "Birthday"
         << left << setw(15) << "Position"
         << left << setw(15) << "Degree"
         << left << setw(15) << "Specialty"
         << "Scientific Works" << endl;
}

void UniversityTeacher::printTable() const {
    cout << left << setw(15) << lastName
         << left << setw(15) << firstName
         << left << setw(15) << middleName
         << left << setw(12) << birthday.toString()
         << left << setw(15) << position
         << left << setw(15) << academicDegree
         << left << setw(15) << specialty;

    if (scientificWorksCount == 0) {
        cout << "-";
    } else {
        for (int i = 0; i < scientificWorksCount; ++i) {
            if (i > 0) cout << ", ";
            cout << scientificWorks[i];
        }
    }
    cout << endl;
}

void UniversityTeacher::updateField(int fieldChoice) {
    string str;
    int num;
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
        case 4: {
            Date d = safeInputDate(cin, "DD/MM/YYYY", "New birthday (DD/MM/YYYY): ");
            setBirthday(d);
            break;
        }
        case 5:
            str = safeGetLine(cin, Language::ENGLISH, "New position: ");
            setPosition(str);
            break;
        case 6:
            str = safeGetLine(cin, Language::ENGLISH, "New academic degree: ");
            setAcademicDegree(str);
            break;
        case 7:
            str = safeGetLine(cin, Language::ENGLISH, "New specialty: ");
            setSpecialty(str);
            break;
        case 8:
            str = safeGetLine(cin, Language::ENGLISH, "New scientific work: ");
            addScientificWork(str);
            break;
        case 9:
            if (scientificWorksCount == 0) {
                cout << "No scientific works to replace." << endl;
            } else {
                num = safeInputNumeric<int>(cin, 0, scientificWorksCount - 1,
                                            "Enter index of scientific work to change (0-" + to_string(scientificWorksCount - 1) + "): ");
                str = safeGetLine(cin, Language::ENGLISH, "Enter new scientific work entry: ");
                setScientificWork(num, str);
            }
            break;
        default:
            break;
    }
}

istream& operator>>(istream& is, UniversityTeacher& teacher) {
    cout << "=== Enter Human Data ===" << endl;
    is >> static_cast<Human&>(teacher);

    teacher.position = safeGetLine(is, Language::ENGLISH, "Enter position: ");
    teacher.academicDegree = safeGetLine(is, Language::ENGLISH, "Enter academic degree: ");
    teacher.specialty = safeGetLine(is, Language::ENGLISH, "Enter specialty: ");

    teacher.scientificWorksCount = safeInputNumeric<int>(is, 0, SCIENTIFIC_WORKS_SIZE,
        "Enter number of scientific works (0-" + to_string(SCIENTIFIC_WORKS_SIZE) + "): ");

    for (int i = 0; i < teacher.scientificWorksCount; ++i) {
        teacher.scientificWorks[i] = safeGetLine(is, Language::ENGLISH, "Enter scientific work " + to_string(i + 1) + ": ");
    }

    return is;
}

void UniversityTeacher::saveTextRecord(ostream& os) const {
    Human::saveTextRecord(os);
    os << ';'
       << position << ';'
       << academicDegree << ';'
       << specialty << ';'
       << scientificWorksCount;
    for (int i = 0; i < scientificWorksCount; ++i) {
        os << ';' << scientificWorks[i];
    }
}

UniversityTeacher* UniversityTeacher::readTextRecord(istream& is) {
    string line;
    if (!getline(is, line)) {
        return nullptr;
    }
    if (line.empty()) {
        return nullptr;
    }

    istringstream iss(line);
    string first, last, middle, dateStr;
    string pos, degree, spec, countStr;

    if (!getline(iss, first, ';') ||
        !getline(iss, last, ';') ||
        !getline(iss, middle, ';') ||
        !getline(iss, dateStr, ';') ||
        !getline(iss, pos, ';') ||
        !getline(iss, degree, ';') ||
        !getline(iss, spec, ';') ||
        !getline(iss, countStr, ';')) {
        throw FileException(80, "Invalid UniversityTeacher text record format");
    }

    Date birth;
    {
        istringstream ds(dateStr);
        ds >> birth;
    }

    int count = 0;
    try {
        count = stoi(countStr);
    } catch (...) {
        throw FileException(81, "Invalid scientific works count in text record");
    }

    UniversityTeacher* t = new UniversityTeacher(first, last, middle, birth, pos, degree, spec);
    t->scientificWorksCount = 0;

    for (int i = 0; i < count && i < SCIENTIFIC_WORKS_SIZE; ++i) {
        string work;
        if (!getline(iss, work, ';')) {
            delete t;
            throw FileException(82, "Invalid scientific work entry in text record");
        }
        t->addScientificWork(work);
    }

    return t;
}

namespace {
    void writeIntUT(ostream& os, int value) {
        os.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }

    int readIntUT(istream& is) {
        int value = 0;
        if (!is.read(reinterpret_cast<char*>(&value), sizeof(value))) {
            throw FileException(83, "Error reading integer from binary file");
        }
        return value;
    }

    void writeStringUT(ostream& os, const string& s) {
        int len = static_cast<int>(s.size());
        writeIntUT(os, len);
        if (len > 0) {
            os.write(s.data(), len);
        }
    }

    string readStringUT(istream& is) {
        int len = readIntUT(is);
        if (len < 0) {
            throw FileException(84, "Negative string length in binary file");
        }
        string s;
        s.resize(len);
        if (len > 0) {
            if (!is.read(&s[0], len)) {
                throw FileException(85, "Error reading string data from binary file");
            }
        }
        return s;
    }
}

void UniversityTeacher::saveBinaryRecord(ostream& os) const {
    writeStringUT(os, firstName);
    writeStringUT(os, lastName);
    writeStringUT(os, middleName);
    writeStringUT(os, birthday.toString());
    writeStringUT(os, position);
    writeStringUT(os, academicDegree);
    writeStringUT(os, specialty);
    writeIntUT(os, scientificWorksCount);
    for (int i = 0; i < scientificWorksCount; ++i) {
        writeStringUT(os, scientificWorks[i]);
    }
}

UniversityTeacher* UniversityTeacher::readBinaryRecord(istream& is) {
    if (is.peek() == EOF) {
        return nullptr;
    }

    string first = readStringUT(is);
    string last = readStringUT(is);
    string middle = readStringUT(is);
    string dateStr = readStringUT(is);
    string pos = readStringUT(is);
    string degree = readStringUT(is);
    string spec = readStringUT(is);
    int count = readIntUT(is);

    Date birth;
    {
        istringstream ds(dateStr);
        ds >> birth;
    }

    UniversityTeacher* t = new UniversityTeacher(first, last, middle, birth, pos, degree, spec);
    t->scientificWorksCount = 0;

    for (int i = 0; i < count && i < SCIENTIFIC_WORKS_SIZE; ++i) {
        string work = readStringUT(is);
        t->addScientificWork(work);
    }

    return t;
}
