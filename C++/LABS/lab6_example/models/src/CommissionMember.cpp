#include "../include/CommissionMember.hpp"
#include "../../exceptions/include/InputHandler.hpp"
#include "../../exceptions/include/FileException.hpp"
#include <sstream>

using namespace std;

CommissionMember::CommissionMember() : Human(), appointmentDate(), autobiographyCount(0) {}

CommissionMember::CommissionMember(const string& first, const string& last, const string& middle, const Date& birth,
                                   const string& commission, const Date& appDate, const string& cert)
    : Human(first, last, middle, birth),
      commissionName(commission),
      appointmentDate(appDate),
      certificateNumber(cert),
      autobiographyCount(0) {}

CommissionMember::~CommissionMember() {}

CommissionMember::CommissionMember(const CommissionMember& other)
    : Human(other),
      commissionName(other.commissionName),
      appointmentDate(other.appointmentDate),
      certificateNumber(other.certificateNumber),
      autobiographyCount(other.autobiographyCount) {
    for (int i = 0; i < autobiographyCount; ++i) {
        autobiography[i] = other.autobiography[i];
    }
}

CommissionMember& CommissionMember::operator=(const CommissionMember& other) {
    if (this != &other) {
        Human::operator=(other);
        commissionName = other.commissionName;
        appointmentDate = other.appointmentDate;
        certificateNumber = other.certificateNumber;
        autobiographyCount = other.autobiographyCount;
        for (int i = 0; i < autobiographyCount; ++i) {
            autobiography[i] = other.autobiography[i];
        }
    }
    return *this;
}

string CommissionMember::getCommissionName() const { return commissionName; }
Date CommissionMember::getAppointmentDate() const { return appointmentDate; }
string CommissionMember::getCertificateNumber() const { return certificateNumber; }

string CommissionMember::getAutobiography(int index) const {
    if (index >= 0 && index < autobiographyCount) {
        return autobiography[index];
    }
    return "";
}

int CommissionMember::getAutobiographyCount() const { return autobiographyCount; }
int CommissionMember::getAutobiographySize() const { return AUTOBIOGRAPHY_SIZE; }

void CommissionMember::setCommissionName(const string& name) { commissionName = name; }
void CommissionMember::setAppointmentDate(const Date& date) { appointmentDate = date; }
void CommissionMember::setCertificateNumber(const string& number) { certificateNumber = number; }

void CommissionMember::setAutobiography(int index, const string& bio) {
    if (index >= 0 && index < AUTOBIOGRAPHY_SIZE) {
        if (index >= autobiographyCount) {
            autobiographyCount = index + 1;
        }
        autobiography[index] = bio;
    }
}

void CommissionMember::addAutobiography(const string& bio) {
    if (autobiographyCount < AUTOBIOGRAPHY_SIZE) {
        autobiography[autobiographyCount++] = bio;
    }
}

void CommissionMember::printHeader() const {
    cout << left << setw(15) << "Last Name"
         << left << setw(15) << "First Name"
         << left << setw(15) << "Middle Name"
         << left << setw(12) << "Birthday"
         << left << setw(20) << "Commission"
         << left << setw(12) << "App.Date"
         << left << setw(15) << "Certificate"
         << "Autobiography" << endl;
}

void CommissionMember::printTable() const {
    cout << left << setw(15) << lastName
         << left << setw(15) << firstName
         << left << setw(15) << middleName
         << left << setw(12) << birthday.toString()
         << left << setw(20) << commissionName
         << left << setw(12) << appointmentDate.toString()
         << left << setw(15) << certificateNumber;

    if (autobiographyCount == 0) {
        cout << "-";
    } else {
        for (int i = 0; i < autobiographyCount; ++i) {
            if (i > 0) cout << ", ";
            cout << autobiography[i];
        }
    }
    cout << endl;
}

void CommissionMember::updateField(int fieldChoice) {
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
            str = safeGetLine(cin, Language::ENGLISH, "New commission name: ");
            setCommissionName(str);
            break;
        case 6: {
            Date d = safeInputDate(cin, "DD/MM/YYYY", "New appointment date (DD/MM/YYYY): ");
            setAppointmentDate(d);
            break;
        }
        case 7:
            str = safeGetLine(cin, Language::ENGLISH, "New certificate number: ");
            setCertificateNumber(str);
            break;
        case 8:
            str = safeGetLine(cin, Language::ENGLISH, "New autobiography entry: ");
            addAutobiography(str);
            break;
        case 9:
            if (autobiographyCount == 0) {
                cout << "No autobiography entries to replace." << endl;
            } else {
                num = safeInputNumeric<int>(cin, 0, autobiographyCount - 1,
                                            "Enter index of autobiography entry to change (0-" + to_string(autobiographyCount - 1) + "): ");
                str = safeGetLine(cin, Language::ENGLISH, "Enter new autobiography entry: ");
                setAutobiography(num, str);
            }
            break;
        default:
            break;
    }
}

istream& operator>>(istream& is, CommissionMember& member) {
    cout << "=== Enter Human Data ===" << endl;
    is >> static_cast<Human&>(member);

    member.commissionName = safeGetLine(is, Language::ENGLISH, "Enter commission name: ");
    member.appointmentDate = safeInputDate(is, "DD/MM/YYYY", "Enter appointment date (DD/MM/YYYY): ");
    member.certificateNumber = safeGetLine(is, Language::ENGLISH, "Enter certificate number: ");

    member.autobiographyCount = safeInputNumeric<int>(is, 0, AUTOBIOGRAPHY_SIZE,
        "Enter number of autobiography entries (0-" + to_string(AUTOBIOGRAPHY_SIZE) + "): ");

    for (int i = 0; i < member.autobiographyCount; ++i) {
        member.autobiography[i] = safeGetLine(is, Language::ENGLISH, "Enter autobiography entry " + to_string(i + 1) + ": ");
    }

    return is;
}

void CommissionMember::saveTextRecord(ostream& os) const {
    Human::saveTextRecord(os);
    os << ';'
       << commissionName << ';'
       << appointmentDate.toString() << ';'
       << certificateNumber << ';'
       << autobiographyCount;
    for (int i = 0; i < autobiographyCount; ++i) {
        os << ';' << autobiography[i];
    }
}

CommissionMember* CommissionMember::readTextRecord(istream& is) {
    string line;
    if (!getline(is, line)) {
        return nullptr;
    }
    if (line.empty()) {
        return nullptr;
    }

    istringstream iss(line);
    string first, last, middle, dateStr;
    string comm, appDateStr, cert, countStr;

    if (!getline(iss, first, ';') ||
        !getline(iss, last, ';') ||
        !getline(iss, middle, ';') ||
        !getline(iss, dateStr, ';') ||
        !getline(iss, comm, ';') ||
        !getline(iss, appDateStr, ';') ||
        !getline(iss, cert, ';') ||
        !getline(iss, countStr, ';')) {
        throw FileException(90, "Invalid CommissionMember text record format");
    }

    Date birth;
    {
        istringstream ds(dateStr);
        ds >> birth;
    }

    Date appDate;
    {
        istringstream ds(appDateStr);
        ds >> appDate;
    }

    int count = 0;
    try {
        count = stoi(countStr);
    } catch (...) {
        throw FileException(91, "Invalid autobiography count in text record");
    }

    CommissionMember* m = new CommissionMember(first, last, middle, birth, comm, appDate, cert);
    m->autobiographyCount = 0;

    for (int i = 0; i < count && i < AUTOBIOGRAPHY_SIZE; ++i) {
        string bio;
        if (!getline(iss, bio, ';')) {
            delete m;
            throw FileException(92, "Invalid autobiography entry in text record");
        }
        m->addAutobiography(bio);
    }

    return m;
}

namespace {
    void writeIntCM(ostream& os, int value) {
        os.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }

    int readIntCM(istream& is) {
        int value = 0;
        if (!is.read(reinterpret_cast<char*>(&value), sizeof(value))) {
            throw FileException(93, "Error reading integer from binary file");
        }
        return value;
    }

    void writeStringCM(ostream& os, const string& s) {
        int len = static_cast<int>(s.size());
        writeIntCM(os, len);
        if (len > 0) {
            os.write(s.data(), len);
        }
    }

    string readStringCM(istream& is) {
        int len = readIntCM(is);
        if (len < 0) {
            throw FileException(94, "Negative string length in binary file");
        }
        string s;
        s.resize(len);
        if (len > 0) {
            if (!is.read(&s[0], len)) {
                throw FileException(95, "Error reading string data from binary file");
            }
        }
        return s;
    }
}

void CommissionMember::saveBinaryRecord(ostream& os) const {
    writeStringCM(os, firstName);
    writeStringCM(os, lastName);
    writeStringCM(os, middleName);
    writeStringCM(os, birthday.toString());
    writeStringCM(os, commissionName);
    writeStringCM(os, appointmentDate.toString());
    writeStringCM(os, certificateNumber);
    writeIntCM(os, autobiographyCount);
    for (int i = 0; i < autobiographyCount; ++i) {
        writeStringCM(os, autobiography[i]);
    }
}

CommissionMember* CommissionMember::readBinaryRecord(istream& is) {
    if (is.peek() == EOF) {
        return nullptr;
    }

    string first = readStringCM(is);
    string last = readStringCM(is);
    string middle = readStringCM(is);
    string dateStr = readStringCM(is);
    string comm = readStringCM(is);
    string appDateStr = readStringCM(is);
    string cert = readStringCM(is);
    int count = readIntCM(is);

    Date birth;
    {
        istringstream ds(dateStr);
        ds >> birth;
    }

    Date appDate;
    {
        istringstream ds(appDateStr);
        ds >> appDate;
    }

    CommissionMember* m = new CommissionMember(first, last, middle, birth, comm, appDate, cert);
    m->autobiographyCount = 0;

    for (int i = 0; i < count && i < AUTOBIOGRAPHY_SIZE; ++i) {
        string bio = readStringCM(is);
        m->addAutobiography(bio);
    }

    return m;
}
