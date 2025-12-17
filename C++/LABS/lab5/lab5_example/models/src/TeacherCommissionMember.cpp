#include "../include/TeacherCommissionMember.hpp"
#include "../../exceptions/include/InputHandler.hpp"
TeacherCommissionMember::TeacherCommissionMember()
    : Human(), UniversityTeacher(), CommissionMember(), commissionWorksCount(0) {
    firstName = ""; lastName = ""; middleName = ""; birthday = Date();
}
TeacherCommissionMember::TeacherCommissionMember(const string& first, const string& last, const string& middle, const Date& birth,
                                                 const string& pos, const string& degree, const string& spec,
                                                 const string& commission, const Date& appDate, const string& cert)
    : Human(first, last, middle, birth),
      UniversityTeacher(first, last, middle, birth, pos, degree, spec),
      CommissionMember(first, last, middle, birth, commission, appDate, cert),
      commissionWorksCount(0) {}
TeacherCommissionMember::~TeacherCommissionMember() {}
TeacherCommissionMember& TeacherCommissionMember::operator=(const TeacherCommissionMember& other) {
    if (this != &other) {
        UniversityTeacher::operator=(other);
        CommissionMember::operator=(other);
        this->commissionWorksCount = other.commissionWorksCount;
        for (int i = 0; i < this->commissionWorksCount; i++) {
            this->commissionWorks[i] = other.commissionWorks[i];
        }
    }
    return *this;
}
bool TeacherCommissionMember::operator==(const TeacherCommissionMember& other) const {
    return UniversityTeacher::operator==(other) &&
           CommissionMember::operator==(other) &&
           this->commissionWorksCount == other.commissionWorksCount;
}
bool TeacherCommissionMember::operator<(const TeacherCommissionMember& other) const {
    return UniversityTeacher::operator<(other);
}
ostream& operator<<(ostream& os, const TeacherCommissionMember& tcm) {
    os << static_cast<const Human&>(tcm) << " " << tcm.UniversityTeacher::getPosition() << " "
       << tcm.UniversityTeacher::getAcademicDegree() << " " << tcm.UniversityTeacher::getSpecialty()
       << " " << tcm.CommissionMember::getCommissionName() << " " << tcm.CommissionMember::getAppointmentDate()
       << " " << tcm.CommissionMember::getCertificateNumber();
    for (int i = 0; i < tcm.UniversityTeacher::getScientificWorksCount(); i++) {
        os << " " << tcm.UniversityTeacher::getScientificWork(i);
    }
    for (int i = 0; i < tcm.CommissionMember::getAutobiographyCount(); i++) {
        os << " " << tcm.CommissionMember::getAutobiography(i);
    }
    for (int i = 0; i < tcm.commissionWorksCount; i++) {
        os << " " << tcm.commissionWorks[i];
    }
    return os;
}
istream& operator>>(istream& is, TeacherCommissionMember& tcm) {
    is >> static_cast<UniversityTeacher&>(tcm);
    cout << "=== Enter CommissionMember Data ===" << endl;
    tcm.CommissionMember::commissionName = safeGetLine(is, Language::ENGLISH, "Enter commission name: ");
    tcm.CommissionMember::appointmentDate = safeInputDate(is, "DD/MM/YYYY", "Enter appointment date: ");
    tcm.CommissionMember::certificateNumber = safeGetLine(is, Language::ENGLISH, "Enter certificate number: ");
    tcm.CommissionMember::autobiographyCount = safeInputNumeric<int>(is, 0, AUTOBIOGRAPHY_SIZE,
                                                  "Enter number of autobiography entries (0-" + to_string(AUTOBIOGRAPHY_SIZE) + "): ");
    for (int i = 0; i < tcm.CommissionMember::autobiographyCount; i++) {
        tcm.CommissionMember::autobiography[i] = safeGetLine(is, Language::ENGLISH, "Enter autobiography entry " + to_string(i + 1) + ": ");
    }
    cout << "=== Enter TeacherCommissionMember Data ===" << endl;
    tcm.commissionWorksCount = safeInputNumeric<int>(is, 0, COMMISSION_WORKS_SIZE,
                                                    "Enter number of commission works (0-" + to_string(COMMISSION_WORKS_SIZE) + "): ");
    for (int i = 0; i < tcm.commissionWorksCount; i++) {
        tcm.commissionWorks[i] = safeGetLine(is, Language::ENGLISH, "Enter commission work " + to_string(i + 1) + ": ");
    }
    return is;
}
string TeacherCommissionMember::getCommissionWork(int index) const {
    if (index >= 0 && index < commissionWorksCount) return this->commissionWorks[index];
    return "";
}
int TeacherCommissionMember::getCommissionWorksCount() const { return this->commissionWorksCount; }
int TeacherCommissionMember::getCommissionWorksSize() const { return COMMISSION_WORKS_SIZE; }
void TeacherCommissionMember::setCommissionWork(int index, const string& work) {
    if (index >= 0 && index < COMMISSION_WORKS_SIZE) {
        if (index >= commissionWorksCount) {
            commissionWorksCount = index + 1;
        }
        this->commissionWorks[index] = work;
    }
}
void TeacherCommissionMember::addCommissionWork(const string& work) {
    if (commissionWorksCount < COMMISSION_WORKS_SIZE) {
        commissionWorks[commissionWorksCount++] = work;
    }
}
void TeacherCommissionMember::printHeader() const {
    cout << "+" << string(14, '-') << "+" << string(14, '-') << "+" << string(14, '-') << "+" << string(12, '-') << "+"
         << string(8, '-') << "+" << string(6, '-') << "+" << string(9, '-') << "+" << string(16, '-') << "+" << string(9, '-') << "+"
         << string(10, '-') << "+" << string(12, '-') << "+" << string(11, '-') << "+" << string(13, '-') << "+" << string(9, '-') << "+"
         << string(10, '-') << "+" << string(10, '-') << "+" << endl;
    cout << "| " << setw(14) << "First Name" << " | " << setw(14) << "Last Name" << " | " << setw(14) << "Middle Name" << " | " << setw(12) << "Birthday" << " |"
         << setw(8) << "Position" << " | " << setw(6) << "Degree" << " | " << setw(9) << "Specialty" << " | " << setw(16) << "Scientific Works" << " | " << setw(9) << "Work Count" << " |"
         << setw(10) << "Commission" << " | " << setw(12) << "Appt. Date" << " | " << setw(11) << "Certificate" << " | " << setw(13) << "Autobiography" << " | " << setw(9) << "Bio Count" << " |"
         << setw(10) << "Comm Works" << " | " << setw(10) << "Comm Count" << " |" << endl;
}
void TeacherCommissionMember::printTable() const {
    string scientificWorksStr;
    for (int i = 0; i < UniversityTeacher::scientificWorksCount; i++) {
        if (i > 0) scientificWorksStr += ", ";
        scientificWorksStr += UniversityTeacher::scientificWorks[i];
    }
    if (scientificWorksStr.length() > 13) scientificWorksStr = scientificWorksStr.substr(0, 10) + "...";
    string autobiographyStr;
    for (int i = 0; i < CommissionMember::autobiographyCount; i++) {
        if (i > 0) autobiographyStr += ", ";
        autobiographyStr += CommissionMember::autobiography[i];
    }
    if (autobiographyStr.length() > 10) autobiographyStr = autobiographyStr.substr(0, 7) + "...";
    string commissionWorksStr;
    for (int i = 0; i < commissionWorksCount; i++) {
        if (i > 0) commissionWorksStr += ", ";
        commissionWorksStr += commissionWorks[i];
    }
    if (commissionWorksStr.length() > 7) commissionWorksStr = commissionWorksStr.substr(0, 4) + "...";
    cout << "| " << setw(14) << firstName << " | " << setw(14) << lastName << " | " << setw(14) << middleName << " | " << setw(12) << birthday << " |"
         << setw(8) << UniversityTeacher::getPosition() << " | " << setw(6) << UniversityTeacher::getAcademicDegree() << " | " << setw(9) << UniversityTeacher::getSpecialty() << " | " << setw(16) << scientificWorksStr << " | " << setw(9) << scientificWorksCount << " | "
         << setw(10) << CommissionMember::getCommissionName() << " | " << setw(12) << CommissionMember::getAppointmentDate() << " | " << setw(11) << CommissionMember::getCertificateNumber() << " | " << setw(13) << autobiographyStr << " | " << setw(9) << autobiographyCount << " | "
         << setw(10) << commissionWorksStr << " | " << setw(10) << commissionWorksCount << " |" << endl;
}
void TeacherCommissionMember::updateField(int fieldChioce) {
    string str;
    int num;
    Date date;
    if(fieldChioce <= 4) {
        Human::updateField(fieldChioce);
        return;
    }
    if(fieldChioce >= 5 && fieldChioce <= 9) {
        if(fieldChioce <= 7) {
            UniversityTeacher::updateField(fieldChioce);
        } else if (fieldChioce == 8) {
            str = safeGetLine(cin, Language::ENGLISH, "New scientific work: ");
            UniversityTeacher::addScientificWork(str);
        } else if (fieldChioce == 9) {
            num = safeInputNumeric<int>(cin, 0, UniversityTeacher::scientificWorksCount - 1, "Enter index of scientific work to change (0-" + to_string(UniversityTeacher::scientificWorksCount - 1) + "): ");
            str = safeGetLine(cin, Language::ENGLISH, "Enter new scientific work entry: ");
            UniversityTeacher::setScientificWork(num, str);
        }
        return;
    }
    if (fieldChioce >= 10 && fieldChioce <= 14) {
        if(fieldChioce == 10) {
            str = safeGetLine(cin, Language::ENGLISH, "New commission name: ");
            CommissionMember::setCommissionName(str);
        } else if(fieldChioce == 11) {
            date = safeInputDate(cin, "DD/MM/YYYY", "New appointment date: ");
            CommissionMember::setAppointmentDate(date);
        } else if(fieldChioce == 12) {
            str = safeGetLine(cin, Language::ENGLISH, "New certificate number: ");
            CommissionMember::setCertificateNumber(str);
        } else if(fieldChioce == 13) {
            str = safeGetLine(cin, Language::ENGLISH, "New autobiography: ");
            CommissionMember::addAutobiography(str);
        } else if(fieldChioce == 14) {
            num = safeInputNumeric<int>(cin, 0, CommissionMember::autobiographyCount - 1, "Enter index of autobiography to change (0-" + to_string(CommissionMember::autobiographyCount - 1) + "): ");
            str = safeGetLine(cin, Language::ENGLISH, "Enter new autobiography entry: ");
            CommissionMember::setAutobiography(num, str);
        }
        return;
    }
    switch(fieldChioce) {
        case 15:
            str = safeGetLine(cin, Language::ENGLISH, "New commission work: ");
            addCommissionWork(str);
            break;
        case 16:
            num = safeInputNumeric<int>(cin, 0, commissionWorksCount - 1, "Enter index of commission work to change (0-" + to_string(commissionWorksCount - 1) + "): ");
            str = safeGetLine(cin, Language::ENGLISH, "Enter new commission work entry: ");
            setCommissionWork(num, str);
            break;
    }
}