#include <iostream>
#include <string>

class Student{

    private:
    std::string name;
    int age;
    float grade;

    public:
    Student(std::string name, int age, float grade);

    void showInfo();

    void setAge(int age);
    void setGrade(float grade);
    int getAge();
    float getGrade();

};