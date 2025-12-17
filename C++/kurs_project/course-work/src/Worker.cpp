#include "../include/Worker.h"
#include <iostream>
#include <iomanip>

Worker::Worker()
    : positionId(0), bonus(0.0) {}

Worker::Worker(int employeeId,
               const std::string& firstName,
               const std::string& lastName,
               int departmentId,
               double salary,
               int positionId,
               double bonus)
    : Employee(employeeId, firstName, lastName, departmentId, salary),
      positionId(positionId),
      bonus(bonus) {}

Worker::~Worker() = default;

int Worker::getPositionId() const {
    return positionId;
}

double Worker::getBonus() const {
    return bonus;
}

void Worker::setPositionId(int positionId) {
    this->positionId = positionId;
}

void Worker::setBonus(double bonus) {
    this->bonus = bonus;
}

void Worker::displayInfo() const {
    std::cout << "Работник #" << employeeId << ": " << getFullName()
              << ", отдел #" << departmentId
              << ", должность #" << positionId
              << ", оклад " << std::fixed << std::setprecision(2) << salary
              << ", премия " << std::fixed << std::setprecision(2) << bonus
              << std::endl;
}

double Worker::calculateTotalIncome() const {
    return salary + bonus;
}

