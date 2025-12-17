#include "../include/HireDate.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace {
bool isValidDate(int day, int month, int year) {
    if (year < 1900 || month < 1 || month > 12 || day < 1) {
        return false;
    }

    constexpr int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int dim = daysInMonth[month - 1];
    const bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (month == 2 && isLeap) {
        dim = 29;
    }
    return day <= dim;
}

bool isValidTime(int hour, int minute) {
    return hour >= 0 && hour < 24 && minute >= 0 && minute < 60;
}
} // namespace

HireDate::HireDate()
    : employeeId(0), day(1), month(1), year(2000), hour(9), minute(0) {}

HireDate::HireDate(int employeeId, int day, int month, int year, int hour, int minute)
    : employeeId(employeeId), day(day), month(month), year(year), hour(hour), minute(minute) {
    if (!isValidDate(day, month, year)) {
        throw std::invalid_argument("Некорректная дата приема на работу");
    }
    if (!isValidTime(hour, minute)) {
        throw std::invalid_argument("Некорректное время приема на работу");
    }
}

HireDate::~HireDate() = default;

int HireDate::getEmployeeId() const {
    return employeeId;
}

int HireDate::getDay() const {
    return day;
}

int HireDate::getMonth() const {
    return month;
}

int HireDate::getYear() const {
    return year;
}

int HireDate::getHour() const {
    return hour;
}

int HireDate::getMinute() const {
    return minute;
}

void HireDate::setEmployeeId(int employeeId) {
    this->employeeId = employeeId;
}

void HireDate::setDay(int day) {
    if (!isValidDate(day, month, year)) {
        throw std::invalid_argument("Некорректный день");
    }
    this->day = day;
}

void HireDate::setMonth(int month) {
    if (!isValidDate(day, month, year)) {
        throw std::invalid_argument("Некорректный месяц");
    }
    this->month = month;
}

void HireDate::setYear(int year) {
    if (!isValidDate(day, month, year)) {
        throw std::invalid_argument("Некорректный год");
    }
    this->year = year;
}

void HireDate::setHour(int hour) {
    if (!isValidTime(hour, minute)) {
        throw std::invalid_argument("Некорректный час");
    }
    this->hour = hour;
}

void HireDate::setMinute(int minute) {
    if (!isValidTime(hour, minute)) {
        throw std::invalid_argument("Некорректная минута");
    }
    this->minute = minute;
}

std::string HireDate::getDateString() const {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << day << "."
        << std::setw(2) << month << "." << std::setw(4) << year;
    return oss.str();
}

std::string HireDate::getTimeString() const {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hour << ":"
        << std::setw(2) << minute;
    return oss.str();
}

std::string HireDate::getFullDateTimeString() const {
    return getDateString() + " " + getTimeString();
}

void HireDate::displayInfo() const {
    std::cout << "Дата приема сотрудника #" << employeeId
              << ": " << getFullDateTimeString() << std::endl;
}

