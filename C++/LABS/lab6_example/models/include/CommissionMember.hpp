#pragma once
#include "Human.hpp"
#include "../../exceptions/include/Date.hpp"

using namespace std;

#define AUTOBIOGRAPHY_SIZE 10

class CommissionMember : virtual public Human {
protected:
    string commissionName;
    Date appointmentDate;
    string certificateNumber;
    string autobiography[AUTOBIOGRAPHY_SIZE];
    int autobiographyCount;
public:
    CommissionMember();
    CommissionMember(const string& first, const string& last, const string& middle, const Date& birth,
                     const string& commission, const Date& appDate, const string& cert);
    virtual ~CommissionMember();
    CommissionMember(const CommissionMember& other);
    CommissionMember& operator=(const CommissionMember& other);

    string getCommissionName() const;
    Date getAppointmentDate() const;
    string getCertificateNumber() const;
    string getAutobiography(int index) const;
    int getAutobiographyCount() const;
    int getAutobiographySize() const;

    void setCommissionName(const string& name);
    void setAppointmentDate(const Date& date);
    void setCertificateNumber(const string& number);
    void setAutobiography(int index, const string& bio);
    void addAutobiography(const string& bio);

    void printHeader() const override;
    void printTable() const override;

    void updateField(int fieldChoice) override;

    void saveTextRecord(ostream& os) const;
    static CommissionMember* readTextRecord(istream& is);

    void saveBinaryRecord(ostream& os) const;
    static CommissionMember* readBinaryRecord(istream& is);

    friend istream& operator>>(istream& is, CommissionMember& member);
};
