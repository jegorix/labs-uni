#include "../include/CommissionMember.hpp"
#include "../../exceptions/include/InputHandler.hpp"
CommissionMember::CommissionMember() : Human(), appointmentDate(), autobiographyCount(0) {}
CommissionMember::CommissionMember(const string& first, const string& last, const string& middle, const Date& birth,
                                   const string& commission, const Date& appDate, const string& cert)
    : Human(first, last, middle, birth), commissionName(commission), appointmentDate(appDate), certificateNumber(cert), autobiographyCount(0) {}
CommissionMember::~CommissionMember() {}
CommissionMember& CommissionMember::operator=(const CommissionMember& other) {
    if (this != &other) {
        Human::operator=(other);
        this->commissionName = other.commissionName;
        this->appointmentDate = other.appointmentDate;
        this->certificateNumber = other.certificateNumber;
        this->autobiographyCount = other.autobiographyCount;
        for (int i = 0; i < autobiographyCount; i++) {
            this->autobiography[i] = other.autobiography[i];
        }
    }
    return *this;
}
bool CommissionMember::operator==(const CommissionMember& other) const {
    return Human::operator==(other) &&
           this->commissionName == other.commissionName &&
           this->appointmentDate == other.appointmentDate &&
           this->certificateNumber == other.certificateNumber &&
           this->autobiographyCount == other.autobiographyCount;
}
bool CommissionMember::operator<(const CommissionMember& other) const {
    return Human::operator<(other);
}
ostream& operator<<(ostream& os, const CommissionMember& member) {
    os << static_cast<const Human&>(member) << " " << member.commissionName << " " << member.appointmentDate << " " << member.certificateNumber;
    for (int i = 0; i < member.autobiographyCount; i++) {
        os << " " << member.autobiography[i];
    }
    return os;
}
istream& operator>>(istream& is, CommissionMember& member) {
    is >> static_cast<Human&>(member);
    member.commissionName = safeGetLine(is, Language::ENGLISH, "Enter commission name: ");
    member.appointmentDate = safeInputDate(is, "DD/MM/YYYY", "Enter appointment date: ");
    member.certificateNumber = safeGetLine(is, Language::ENGLISH, "Enter certificate number: ");
    member.autobiographyCount = safeInputNumeric<int>(is, 0, AUTOBIOGRAPHY_SIZE,
                                             "Enter number of autobiography entries (0-" + to_string(AUTOBIOGRAPHY_SIZE) + "): ");
    for (int i = 0; i < member.autobiographyCount; i++) {
        member.autobiography[i] = safeGetLine(is, Language::ENGLISH, "Enter autobiography entry " + to_string(i + 1) + ": ");
    }
    return is;
}
string CommissionMember::getCommissionName() const { return this->commissionName; }
Date CommissionMember::getAppointmentDate() const { return this->appointmentDate; }
string CommissionMember::getCertificateNumber() const { return this->certificateNumber; }
string CommissionMember::getAutobiography(int index) const {
    if (index >= 0 && index < autobiographyCount) return this->autobiography[index];
    return "";
}
int CommissionMember::getAutobiographyCount() const { return this->autobiographyCount; }
int CommissionMember::getAutobiographySize() const { return AUTOBIOGRAPHY_SIZE; }
void CommissionMember::setCommissionName(const string& name) { this->commissionName = name; }
void CommissionMember::setAppointmentDate(const Date& date) { this->appointmentDate = date; }
void CommissionMember::setCertificateNumber(const string& cert) { this->certificateNumber = cert; }
void CommissionMember::setAutobiography(int index, const string& bio) {
    if (index >= 0 && index < AUTOBIOGRAPHY_SIZE) {
        if (index >= autobiographyCount) {
            autobiographyCount = index + 1;
        }
        this->autobiography[index] = bio;
    }
}
void CommissionMember::addAutobiography(const string& entry) {
    if (autobiographyCount < AUTOBIOGRAPHY_SIZE) {
        autobiography[autobiographyCount++] = entry;
    }
}
void CommissionMember::printHeader() const {
    Human::printHeader();
    cout << string(1, '-') << string(10, '-') << string(1, '-') << " | "
         << string(1, '-') << string(12, '-') << string(1, '-') << " | "
         << string(1, '-') << string(11, '-') << string(1, '-') << " | "
         << string(1, '-') << string(13, '-') << string(1, '-') << " | "
         << string(1, '-') << string(9, '-') << string(1, '-') << " |" << endl;
    cout << "| " << setw(14) << "First Name" << " | " << setw(14) << "Last Name"
         << " | " << setw(14) << "Middle Name" << " | " << setw(12) << "Birthday" << " | "
         << setw(10) << "Commission" << " | " << setw(12) << "Appt. Date"
         << " | " << setw(11) << "Certificate" << " | " << setw(13) << "Autobiography"
         << " | " << setw(9) << "Bio Count" << " |" << endl;
}
void CommissionMember::printTable() const {
    Human::printTable();
    string autobiographyStr;
    for (int i = 0; i < autobiographyCount; i++) {
        if (i > 0) autobiographyStr += ", ";
        autobiographyStr += autobiography[i];
    }
    if (autobiographyStr.length() > 10) autobiographyStr = autobiographyStr.substr(0, 7) + "...";
    cout << " | " << setw(10) << this->commissionName << " | " << setw(12) << this->appointmentDate
         << " | " << setw(11) << this->certificateNumber << " | " << setw(13) << autobiographyStr
         << " | " << setw(9) << this->autobiographyCount << " |" << endl;
}
void CommissionMember::updateField(int fieldChioce) {
    string str;
    int num;
    Date date;
    if(fieldChioce <= 4) {
        Human::updateField(fieldChioce);
        return;
    }
    switch(fieldChioce) {
        case 5:
            str = safeGetLine(cin, Language::ENGLISH, "New commission name: ");
            setCommissionName(str);
            break;
        case 6:
            date = safeInputDate(cin, "DD/MM/YYYY", "New appointment date: ");
            setAppointmentDate(date);
            break;
        case 7:
            str = safeGetLine(cin, Language::ENGLISH, "New certificate number: ");
            setCertificateNumber(str);
            break;
        case 8:
            str = safeGetLine(cin, Language::ENGLISH, "New autobiography: ");
            addAutobiography(str);
            break;
        case 9:
            num = safeInputNumeric<int>(cin, 0, autobiographyCount - 1, "Enter index of autobiography to change (0-" + to_string(autobiographyCount - 1) + "): ");
            str = safeGetLine(cin, Language::ENGLISH, "Enter new autobiography entry: ");
            setAutobiography(num, str);
            break;
    }
}