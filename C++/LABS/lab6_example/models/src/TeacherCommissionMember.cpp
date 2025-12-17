#include "../include/TeacherCommissionMember.hpp"
#include "../../exceptions/include/InputHandler.hpp"
#include "../../exceptions/include/FileException.hpp"
#include <sstream>

using namespace std;

TeacherCommissionMember::TeacherCommissionMember()
    : Human(),
      UniversityTeacher(),
      CommissionMember(),
      commissionWorksCount(0) {}

TeacherCommissionMember::TeacherCommissionMember(const string& first, const string& last, const string& middle, const Date& birth,
                                                 const string& pos, const string& degree, const string& spec,
                                                 const string& commission, const Date& appDate, const string& cert)
    : Human(first, last, middle, birth),
      UniversityTeacher(first, last, middle, birth, pos, degree, spec),
      CommissionMember(first, last, middle, birth, commission, appDate, cert),
      commissionWorksCount(0) {}

TeacherCommissionMember::~TeacherCommissionMember() {}

TeacherCommissionMember::TeacherCommissionMember(const TeacherCommissionMember& other)
    : Human(other),
      UniversityTeacher(other),
      CommissionMember(other),
      commissionWorksCount(other.commissionWorksCount) {
    for (int i = 0; i < commissionWorksCount; ++i) {
        commissionWorks[i] = other.commissionWorks[i];
    }
}

TeacherCommissionMember& TeacherCommissionMember::operator=(const TeacherCommissionMember& other) {
    if (this != &other) {
        UniversityTeacher::operator=(other);
        CommissionMember::operator=(other);
        commissionWorksCount = other.commissionWorksCount;
        for (int i = 0; i < commissionWorksCount; ++i) {
            commissionWorks[i] = other.commissionWorks[i];
        }
    }
    return *this;
}

string TeacherCommissionMember::getCommissionWork(int index) const {
    if (index >= 0 && index < commissionWorksCount) {
        return commissionWorks[index];
    }
    return "";
}

int TeacherCommissionMember::getCommissionWorksCount() const { return commissionWorksCount; }
int TeacherCommissionMember::getCommissionWorksSize() const { return COMMISSION_WORKS_SIZE; }

void TeacherCommissionMember::setCommissionWork(int index, const string& work) {
    if (index >= 0 && index < COMMISSION_WORKS_SIZE) {
        if (index >= commissionWorksCount) {
            commissionWorksCount = index + 1;
        }
        commissionWorks[index] = work;
    }
}

void TeacherCommissionMember::addCommissionWork(const string& work) {
    if (commissionWorksCount < COMMISSION_WORKS_SIZE) {
        commissionWorks[commissionWorksCount++] = work;
    }
}

void TeacherCommissionMember::printHeader() const {
    cout << left << setw(15) << "Last Name"
         << left << setw(15) << "First Name"
         << left << setw(15) << "Middle Name"
         << left << setw(12) << "Birthday"
         << left << setw(15) << "Position"
         << left << setw(15) << "Degree"
         << left << setw(15) << "Specialty"
         << left << setw(20) << "Commission"
         << left << setw(12) << "App.Date"
         << left << setw(15) << "Certificate"
         << left << setw(20) << "Scientific Works"
         << "Commission Works" << endl;
}

void TeacherCommissionMember::printTable() const {
    cout << left << setw(15) << lastName
         << left << setw(15) << firstName
         << left << setw(15) << middleName
         << left << setw(12) << birthday.toString()
         << left << setw(15) << position
         << left << setw(15) << academicDegree
         << left << setw(15) << specialty
         << left << setw(20) << commissionName
         << left << setw(12) << appointmentDate.toString()
         << left << setw(15) << certificateNumber;

    if (scientificWorksCount == 0) {
        cout << left << setw(20) << "-";
    } else {
        string allSci;
        for (int i = 0; i < scientificWorksCount; ++i) {
            if (i > 0) allSci += ", ";
            allSci += scientificWorks[i];
        }
        cout << left << setw(20) << allSci;
    }

    if (commissionWorksCount == 0) {
        cout << "-";
    } else {
        for (int i = 0; i < commissionWorksCount; ++i) {
            if (i > 0) cout << ", ";
            cout << commissionWorks[i];
        }
    }

    cout << endl;
}

void TeacherCommissionMember::updateField(int fieldChoice) {
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
        case 10:
            str = safeGetLine(cin, Language::ENGLISH, "New commission name: ");
            setCommissionName(str);
            break;
        case 11: {
            Date d = safeInputDate(cin, "DD/MM/YYYY", "New appointment date (DD/MM/YYYY): ");
            setAppointmentDate(d);
            break;
        }
        case 12:
            str = safeGetLine(cin, Language::ENGLISH, "New certificate number: ");
            setCertificateNumber(str);
            break;
        case 13:
            str = safeGetLine(cin, Language::ENGLISH, "New autobiography entry: ");
            addAutobiography(str);
            break;
        case 14:
            if (autobiographyCount == 0) {
                cout << "No autobiography entries to replace." << endl;
            } else {
                num = safeInputNumeric<int>(cin, 0, autobiographyCount - 1,
                                            "Enter index of autobiography entry to change (0-" + to_string(autobiographyCount - 1) + "): ");
                str = safeGetLine(cin, Language::ENGLISH, "Enter new autobiography entry: ");
                setAutobiography(num, str);
            }
            break;
        case 15:
            str = safeGetLine(cin, Language::ENGLISH, "New commission work: ");
            addCommissionWork(str);
            break;
        case 16:
            if (commissionWorksCount == 0) {
                cout << "No commission works to replace." << endl;
            } else {
                num = safeInputNumeric<int>(cin, 0, commissionWorksCount - 1,
                                            "Enter index of commission work to change (0-" + to_string(commissionWorksCount - 1) + "): ");
                str = safeGetLine(cin, Language::ENGLISH, "Enter new commission work entry: ");
                setCommissionWork(num, str);
            }
            break;
        default:
            break;
    }
}

istream& operator>>(istream& is, TeacherCommissionMember& member) {
    cout << "=== Enter Teacher Data ===" << endl;
    is >> static_cast<UniversityTeacher&>(member);

    cout << "=== Enter Commission Member Data ===" << endl;
    member.commissionName = safeGetLine(is, Language::ENGLISH, "Enter commission name: ");
    member.appointmentDate = safeInputDate(is, "DD/MM/YYYY", "Enter appointment date (DD/MM/YYYY): ");
    member.certificateNumber = safeGetLine(is, Language::ENGLISH, "Enter certificate number: ");

    member.autobiographyCount = safeInputNumeric<int>(is, 0, AUTOBIOGRAPHY_SIZE,
        "Enter number of autobiography entries (0-" + to_string(AUTOBIOGRAPHY_SIZE) + "): ");

    for (int i = 0; i < member.autobiographyCount; ++i) {
        member.autobiography[i] = safeGetLine(is, Language::ENGLISH, "Enter autobiography entry " + to_string(i + 1) + ": ");
    }

    cout << "=== Enter Teacher Commission Member Data ===" << endl;
    member.commissionWorksCount = safeInputNumeric<int>(is, 0, COMMISSION_WORKS_SIZE,
        "Enter number of commission works (0-" + to_string(COMMISSION_WORKS_SIZE) + "): ");

    for (int i = 0; i < member.commissionWorksCount; ++i) {
        member.commissionWorks[i] = safeGetLine(is, Language::ENGLISH, "Enter commission work " + to_string(i + 1) + ": ");
    }

    return is;
}

void TeacherCommissionMember::saveTextRecord(ostream& os) const {
    Human::saveTextRecord(os);
    os << ';'
       << position << ';'
       << academicDegree << ';'
       << specialty << ';'
       << scientificWorksCount;
    for (int i = 0; i < scientificWorksCount; ++i) {
        os << ';' << scientificWorks[i];
    }
    os << ';'
       << commissionName << ';'
       << appointmentDate.toString() << ';'
       << certificateNumber << ';'
       << autobiographyCount;
    for (int i = 0; i < autobiographyCount; ++i) {
        os << ';' << autobiography[i];
    }
    os << ';'
       << commissionWorksCount;
    for (int i = 0; i < commissionWorksCount; ++i) {
        os << ';' << commissionWorks[i];
    }
}

TeacherCommissionMember* TeacherCommissionMember::readTextRecord(istream& is) {
    string line;
    if (!getline(is, line)) {
        return nullptr;
    }
    if (line.empty()) {
        return nullptr;
    }

    istringstream iss(line);
    string first, last, middle, dateStr;
    string pos, degree, spec, sciCountStr;
    string comm, appDateStr, cert, autoCountStr;
    string worksCountStr;

    if (!getline(iss, first, ';') ||
        !getline(iss, last, ';') ||
        !getline(iss, middle, ';') ||
        !getline(iss, dateStr, ';') ||
        !getline(iss, pos, ';') ||
        !getline(iss, degree, ';') ||
        !getline(iss, spec, ';') ||
        !getline(iss, sciCountStr, ';')) {
        throw FileException(100, "Invalid TeacherCommissionMember text record format (header)");
    }

    Date birth;
    {
        istringstream ds(dateStr);
        ds >> birth;
    }

    int sciCount = 0;
    try {
        sciCount = stoi(sciCountStr);
    } catch (...) {
        throw FileException(101, "Invalid scientific works count in text record");
    }

    if (!getline(iss, comm, ';') ||
        !getline(iss, appDateStr, ';') ||
        !getline(iss, cert, ';') ||
        !getline(iss, autoCountStr, ';')) {
        throw FileException(102, "Invalid TeacherCommissionMember text record format (commission)");
    }

    Date appDate;
    {
        istringstream ds(appDateStr);
        ds >> appDate;
    }

    int autoCount = 0;
    try {
        autoCount = stoi(autoCountStr);
    } catch (...) {
        throw FileException(103, "Invalid autobiography count in text record");
    }

    if (!getline(iss, worksCountStr, ';')) {
        throw FileException(104, "Invalid TeacherCommissionMember text record format (works count)");
    }

    int worksCount = 0;
    try {
        worksCount = stoi(worksCountStr);
    } catch (...) {
        throw FileException(105, "Invalid commission works count in text record");
    }

    TeacherCommissionMember* m = new TeacherCommissionMember(first, last, middle, birth, pos, degree, spec, comm, appDate, cert);
    m->scientificWorksCount = 0;
    for (int i = 0; i < sciCount && i < SCIENTIFIC_WORKS_SIZE; ++i) {
        string work;
        if (!getline(iss, work, ';')) {
            delete m;
            throw FileException(106, "Invalid scientific work entry in text record");
        }
        m->addScientificWork(work);
    }

    m->autobiographyCount = 0;
    for (int i = 0; i < autoCount && i < AUTOBIOGRAPHY_SIZE; ++i) {
        string bio;
        if (!getline(iss, bio, ';')) {
            delete m;
            throw FileException(107, "Invalid autobiography entry in text record");
        }
        m->addAutobiography(bio);
    }

    m->commissionWorksCount = 0;
    for (int i = 0; i < worksCount && i < COMMISSION_WORKS_SIZE; ++i) {
        string work;
        if (!getline(iss, work, ';')) {
            delete m;
            throw FileException(108, "Invalid commission work entry in text record");
        }
        m->addCommissionWork(work);
    }

    return m;
}

namespace {
    void writeIntTCM(ostream& os, int value) {
        os.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }

    int readIntTCM(istream& is) {
        int value = 0;
        if (!is.read(reinterpret_cast<char*>(&value), sizeof(value))) {
            throw FileException(109, "Error reading integer from binary file");
        }
        return value;
    }

    void writeStringTCM(ostream& os, const string& s) {
        int len = static_cast<int>(s.size());
        writeIntTCM(os, len);
        if (len > 0) {
            os.write(s.data(), len);
        }
    }

    string readStringTCM(istream& is) {
        int len = readIntTCM(is);
        if (len < 0) {
            throw FileException(110, "Negative string length in binary file");
        }
        string s;
        s.resize(len);
        if (len > 0) {
            if (!is.read(&s[0], len)) {
                throw FileException(111, "Error reading string data from binary file");
            }
        }
        return s;
    }
}

void TeacherCommissionMember::saveBinaryRecord(ostream& os) const {
    writeStringTCM(os, firstName);
    writeStringTCM(os, lastName);
    writeStringTCM(os, middleName);
    writeStringTCM(os, birthday.toString());
    writeStringTCM(os, position);
    writeStringTCM(os, academicDegree);
    writeStringTCM(os, specialty);
    writeIntTCM(os, scientificWorksCount);
    for (int i = 0; i < scientificWorksCount; ++i) {
        writeStringTCM(os, scientificWorks[i]);
    }
    writeStringTCM(os, commissionName);
    writeStringTCM(os, appointmentDate.toString());
    writeStringTCM(os, certificateNumber);
    writeIntTCM(os, autobiographyCount);
    for (int i = 0; i < autobiographyCount; ++i) {
        writeStringTCM(os, autobiography[i]);
    }
    writeIntTCM(os, commissionWorksCount);
    for (int i = 0; i < commissionWorksCount; ++i) {
        writeStringTCM(os, commissionWorks[i]);
    }
}

TeacherCommissionMember* TeacherCommissionMember::readBinaryRecord(istream& is) {
    if (is.peek() == EOF) {
        return nullptr;
    }

    string first = readStringTCM(is);
    string last = readStringTCM(is);
    string middle = readStringTCM(is);
    string dateStr = readStringTCM(is);
    string pos = readStringTCM(is);
    string degree = readStringTCM(is);
    string spec = readStringTCM(is);
    int sciCount = readIntTCM(is);
    string comm = readStringTCM(is);
    string appDateStr = readStringTCM(is);
    string cert = readStringTCM(is);
    int autoCount = readIntTCM(is);
    int worksCount = readIntTCM(is);

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

    TeacherCommissionMember* m = new TeacherCommissionMember(first, last, middle, birth, pos, degree, spec, comm, appDate, cert);
    m->scientificWorksCount = 0;
    for (int i = 0; i < sciCount && i < SCIENTIFIC_WORKS_SIZE; ++i) {
        string work = readStringTCM(is);
        m->addScientificWork(work);
    }

    m->autobiographyCount = 0;
    for (int i = 0; i < autoCount && i < AUTOBIOGRAPHY_SIZE; ++i) {
        string bio = readStringTCM(is);
        m->addAutobiography(bio);
    }

    m->commissionWorksCount = 0;
    for (int i = 0; i < worksCount && i < COMMISSION_WORKS_SIZE; ++i) {
        string work = readStringTCM(is);
        m->addCommissionWork(work);
    }

    return m;
}
