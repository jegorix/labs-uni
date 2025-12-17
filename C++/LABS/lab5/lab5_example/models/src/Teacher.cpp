#include "../include/Teacher.hpp"
#include "../../exceptions/include/InputHandler.hpp"
UniversityTeacher::UniversityTeacher() : Human(), scientificWorksCount(0) {}
UniversityTeacher::UniversityTeacher(const string& first, const string& last, const string& middle, const Date& birth,
                                     const string& pos, const string& degree, const string& spec)
    : Human(first, last, middle, birth), position(pos), academicDegree(degree), specialty(spec), scientificWorksCount(0) {}
UniversityTeacher::~UniversityTeacher() {}
UniversityTeacher& UniversityTeacher::operator=(const UniversityTeacher& other) {
    if (this != &other) {
        Human::operator=(other);
        this->position = other.position;
        this->academicDegree = other.academicDegree;
        this->specialty = other.specialty;
        this->scientificWorksCount = other.scientificWorksCount;
        for (int i = 0; i < scientificWorksCount; i++) {
            this->scientificWorks[i] = other.scientificWorks[i];
        }
    }
    return *this;
}
bool UniversityTeacher::operator==(const UniversityTeacher& other) const {
    return Human::operator==(other) &&
           this->position == other.position &&
           this->academicDegree == other.academicDegree &&
           this->specialty == other.specialty &&
           this->scientificWorksCount == other.scientificWorksCount;
}
bool UniversityTeacher::operator<(const UniversityTeacher& other) const {
    return Human::operator<(other);
}
ostream& operator<<(ostream& os, const UniversityTeacher& teacher) {
    os << static_cast<const Human&>(teacher) << " " << teacher.position << " " << teacher.academicDegree << " " << teacher.specialty;
    for (int i = 0; i < teacher.scientificWorksCount; i++) {
        os << " " << teacher.scientificWorks[i];
    }
    return os;
}
istream& operator>>(istream& is, UniversityTeacher& teacher) {
    is >> static_cast<Human&>(teacher);
    teacher.position = safeGetLine(is, Language::ENGLISH, "Enter position: ");
    teacher.academicDegree = safeGetLine(is, Language::ENGLISH, "Enter academic degree: ");
    teacher.specialty = safeGetLine(is, Language::ENGLISH, "Enter specialty: ");
    teacher.scientificWorksCount = safeInputNumeric<int>(is, 0, SCIENTIFIC_WORKS_SIZE,
                                                        "Enter number of scientific works (0-" + to_string(SCIENTIFIC_WORKS_SIZE) + "): ");
    for (int i = 0; i < teacher.scientificWorksCount; i++) {
        teacher.scientificWorks[i] = safeGetLine(is, Language::ENGLISH, "Enter scientific work " + to_string(i + 1) + ": ");
    }
    return is;
}
string UniversityTeacher::getPosition() const { return this->position; }
string UniversityTeacher::getAcademicDegree() const { return this->academicDegree; }
string UniversityTeacher::getSpecialty() const { return this->specialty; }
string UniversityTeacher::getScientificWork(int index) const {
    if (index >= 0 && index < scientificWorksCount) return this->scientificWorks[index];
    return "";
}
int UniversityTeacher::getScientificWorksCount() const { return this->scientificWorksCount; }
int UniversityTeacher::getScientificWorksSize() const { return SCIENTIFIC_WORKS_SIZE; }
void UniversityTeacher::setPosition(const string& pos) { this->position = pos; }
void UniversityTeacher::setAcademicDegree(const string& degree) { this->academicDegree = degree; }
void UniversityTeacher::setSpecialty(const string& spec) { this->specialty = spec; }
void UniversityTeacher::setScientificWork(int index, const string& work) {
    if (index >= 0 && index < SCIENTIFIC_WORKS_SIZE) {
        if (index >= scientificWorksCount) {
            scientificWorksCount = index + 1;
        }
        this->scientificWorks[index] = work;
    }
}
void UniversityTeacher::addScientificWork(const string& work) {
    if (scientificWorksCount < SCIENTIFIC_WORKS_SIZE) {
        scientificWorks[scientificWorksCount++] = work;
    }
}
void UniversityTeacher::printHeader() const {
    Human::printHeader();
    cout << string(1, '-') << string(8, '-') << string(1, '-') << " | "
         << string(1, '-') << string(6, '-') << string(1, '-') << " | "
         << string(1, '-') << string(9, '-') << string(1, '-') << " | "
         << string(1, '-') << string(16, '-') << string(1, '-') << " | "
         << string(1, '-') << string(9, '-') << string(1, '-') << " |" << endl;
    cout << "| " << setw(14) << "First Name" << " | " << setw(14) << "Last Name"
         << " | " << setw(14) << "Middle Name" << " | " << setw(12) << "Birthday" << " | "
         << setw(8) << "Position" << " | " << setw(6) << "Degree"
         << " | " << setw(9) << "Specialty" << " | " << setw(16) << "Scientific Works"
         << " | " << setw(9) << "Work Count" << " |" << endl;
}
void UniversityTeacher::printTable() const {
    Human::printTable();
    string scientificWorksStr;
    for (int i = 0; i < scientificWorksCount; i++) {
        if (i > 0) scientificWorksStr += ", ";
        scientificWorksStr += scientificWorks[i];
    }
    if (scientificWorksStr.length() > 13) scientificWorksStr = scientificWorksStr.substr(0, 10) + "...";
    cout << " | " << setw(8) << this->position << " | " << setw(6) << this->academicDegree
         << " | " << setw(9) << this->specialty << " | " << setw(16) << scientificWorksStr
         << " | " << setw(9) << this->scientificWorksCount << " |" << endl;
}
void UniversityTeacher::updateField(int fieldChioce) {
    string str;
    int num;
    if(fieldChioce <= 4) {
        Human::updateField(fieldChioce);
        return;
    }
    switch(fieldChioce) {
        case 5:
            str = safeGetLine(cin, Language::ENGLISH, "New position: ");
            setPosition(str);
            break;
        case 6:
            str = safeGetLine(cin, Language::ENGLISH, "New degree: ");
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
            num = safeInputNumeric<int>(cin, 0, scientificWorksCount - 1, "Enter index of scientific work to change (0-" + to_string(scientificWorksCount - 1) + "): ");
            str = safeGetLine(cin, Language::ENGLISH, "Enter new scientific work entry: ");
            setScientificWork(num, str);
            break;
    }
}