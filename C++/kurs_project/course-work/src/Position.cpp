#include "../include/Position.h"
#include <iostream>

Position::Position()
    : positionId(0), workHoursPerWeek(40) {}

Position::Position(int positionId, const std::string& positionName, int workHoursPerWeek)
    : positionId(positionId),
      positionName(positionName),
      workHoursPerWeek(workHoursPerWeek) {}

Position::~Position() = default;

int Position::getPositionId() const {
    return positionId;
}

std::string Position::getPositionName() const {
    return positionName;
}

int Position::getWorkHoursPerWeek() const {
    return workHoursPerWeek;
}

void Position::setPositionId(int positionId) {
    this->positionId = positionId;
}

void Position::setPositionName(const std::string& positionName) {
    this->positionName = positionName;
}

void Position::setWorkHoursPerWeek(int workHoursPerWeek) {
    this->workHoursPerWeek = workHoursPerWeek;
}

void Position::displayInfo() const {
    std::cout << "Должность #" << positionId << ": " << positionName
              << ", " << workHoursPerWeek << " ч/нед" << std::endl;
}

