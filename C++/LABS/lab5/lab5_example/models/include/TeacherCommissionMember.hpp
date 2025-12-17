#pragma once
#include "Teacher.hpp"
#include "CommissionMember.hpp"

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
    ~TeacherCommissionMember();
    
    TeacherCommissionMember& operator=(const TeacherCommissionMember& other);
    bool operator==(const TeacherCommissionMember& other) const;
    bool operator<(const TeacherCommissionMember& other) const;
    friend ostream& operator<<(ostream& os, const TeacherCommissionMember& tcm);
    friend istream& operator>>(istream& is, TeacherCommissionMember& tcm);
    
    string getFirstName() const { return UniversityTeacher::getFirstName(); }
    string getLastName() const { return UniversityTeacher::getLastName(); }
    string getMiddleName() const { return UniversityTeacher::getMiddleName(); }
    Date getBirthday() const { return UniversityTeacher::getBirthday(); }
    
    string getCommissionWork(int index) const;
    int getCommissionWorksCount() const;
    int getCommissionWorksSize() const;
    void setCommissionWork(int index, const string& work);
    void addCommissionWork(const string& work);
    
    void printHeader() const override;
    void printTable() const override;

    void updateField(int fieldChoice) override;

};