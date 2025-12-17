#pragma once
#include "Teacher.hpp"
#include "CommissionMember.hpp"

using namespace std;

#define COMMISSION_WORKS_SIZE 5

class TeacherCommissionMember : public UniversityTeacher, public CommissionMember {
private:
    string commissionWorks[COMMISSION_WORKS_SIZE];
    int commissionWorksCount;
public:
    TeacherCommissionMember();
    TeacherCommissionMember(const string& first, const string& last, const string& middle, const Date& birth,
                            const string& pos, const string& degree, const string& spec,
                            const string& commission, const Date& appDate, const string& cert);
    virtual ~TeacherCommissionMember();
    TeacherCommissionMember(const TeacherCommissionMember& other);
    TeacherCommissionMember& operator=(const TeacherCommissionMember& other);

    string getCommissionWork(int index) const;
    int getCommissionWorksCount() const;
    int getCommissionWorksSize() const;

    void setCommissionWork(int index, const string& work);
    void addCommissionWork(const string& work);

    void printHeader() const override;
    void printTable() const override;

    void updateField(int fieldChoice) override;

    void saveTextRecord(ostream& os) const;
    static TeacherCommissionMember* readTextRecord(istream& is);

    void saveBinaryRecord(ostream& os) const;
    static TeacherCommissionMember* readBinaryRecord(istream& is);

    friend istream& operator>>(istream& is, TeacherCommissionMember& member);
};
