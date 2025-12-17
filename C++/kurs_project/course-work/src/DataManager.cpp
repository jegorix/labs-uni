#include "../include/DataManager.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdexcept>

namespace {

std::string trim(const std::string& str) {
    const auto first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return {};
    }
    const auto last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last - first + 1);
}

std::vector<std::string> split(const std::string& line, char delimiter) {
    std::vector<std::string> parts;
    std::stringstream ss(line);
    std::string item;
    while (std::getline(ss, item, delimiter)) {
        parts.push_back(trim(item));
    }
    return parts;
}

std::string combinePath(const std::string& base, const std::string& name) {
    if (base.empty()) {
        return name;
    }
    const char back = base.back();
    if (back == '/' || back == '\\') {
        return base + name;
    }
    return base + "/" + name;
}

} // namespace

DataManager::DataManager(const std::string& dataDirectory) {
    employeesPath = combinePath(dataDirectory, "employees.txt");
    departmentsPath = combinePath(dataDirectory, "departments.txt");
    positionsPath = combinePath(dataDirectory, "positions.txt");
    hiresPath = combinePath(dataDirectory, "hires.txt");
}

void DataManager::loadAll() {
    employees.clear();
    departments.clear();
    positions.clear();
    employeeIndex.clear();
    departmentIndex.clear();
    positionIndex.clear();
    undoStack.clear();

    nextEmployeeId = 1;
    nextDepartmentId = 1;
    nextPositionId = 1;

    loadPositions();
    loadDepartments();
    loadEmployees();
    loadHireDates();
}

void DataManager::saveAll() const {
    savePositions();
    saveDepartments();
    saveEmployees();
    saveHireDates();
}

const RecordCollection<EmployeeRecord>& DataManager::getEmployees() const {
    return employees;
}

RecordCollection<EmployeeRecord>& DataManager::getEmployees() {
    return employees;
}

const RecordCollection<Department>& DataManager::getDepartments() const {
    return departments;
}

RecordCollection<Department>& DataManager::getDepartments() {
    return departments;
}

const RecordCollection<Position>& DataManager::getPositions() const {
    return positions;
}

RecordCollection<Position>& DataManager::getPositions() {
    return positions;
}

int DataManager::addWorker(const std::string& firstName,
                           const std::string& lastName,
                           int departmentId,
                           double salary,
                           int positionId,
                           double bonus,
                           const HireDate& hireDate) {
    const int newId = generateEmployeeId();
    if (!findDepartment(departmentId)) {
        throw std::runtime_error("Указанный отдел не существует");
    }
    if (!findPosition(positionId)) {
        throw std::runtime_error("Указанная должность не существует");
    }
    auto worker = std::make_shared<Worker>(newId, firstName, lastName, departmentId, salary, positionId, bonus);
    EmployeeRecord record{worker, hireDate};
    record.hireDate.setEmployeeId(newId);

    employees.add(record);
    registerEmployee(record);
    ensureDepartmentContainsEmployee(departmentId, newId);

    if (!undoInProgress) {
        pushUndo([this, newId]() {
        removeEmployee(newId);
        }, "Отмена добавления сотрудника");
    }

    return newId;
}

int DataManager::addManager(const std::string& firstName,
                            const std::string& lastName,
                            int departmentId,
                            double salary,
                            const std::vector<int>& subordinateIds,
                            const HireDate& hireDate) {
    const int newId = generateEmployeeId();
    if (!findDepartment(departmentId)) {
        throw std::runtime_error("Указанный отдел не существует");
    }
    std::vector<int> validSubordinates;
    for (int subordinateId : subordinateIds) {
        if (findEmployeeRecord(subordinateId)) {
            validSubordinates.push_back(subordinateId);
        }
    }
    auto manager = std::make_shared<Manager>(newId, firstName, lastName, departmentId, salary, validSubordinates);
    EmployeeRecord record{manager, hireDate};
    record.hireDate.setEmployeeId(newId);

    employees.add(record);
    registerEmployee(record);
    ensureDepartmentContainsEmployee(departmentId, newId);

    if (!undoInProgress) {
        pushUndo([this, newId]() {
        removeEmployee(newId);
        }, "Отмена добавления менеджера");
    }

    return newId;
}

bool DataManager::removeEmployee(int employeeId) {
    const auto it = employeeIndex.find(employeeId);
    if (it == employeeIndex.end()) {
        return false;
    }

    EmployeeRecord record = employees.data().at(it->second);
    std::vector<int> managerIds;
    for (const auto& entry : employees.data()) {
        if (auto manager = std::dynamic_pointer_cast<Manager>(entry.employee)) {
            if (manager->hasSubordinate(employeeId)) {
                managerIds.push_back(manager->getEmployeeId());
            }
        }
    }

    if (!undoInProgress) {
        pushUndo([this, record, managerIds]() {
        EmployeeRecord restored{cloneEmployee(*record.employee), record.hireDate};
        employees.add(restored);
        registerEmployee(restored);
        ensureDepartmentContainsEmployee(restored.employee->getDepartmentId(), restored.employee->getEmployeeId());
        for (int managerId : managerIds) {
            if (auto* managerRecord = findEmployeeRecord(managerId)) {
                if (auto managerPtr = std::dynamic_pointer_cast<Manager>(managerRecord->employee)) {
                    managerPtr->addSubordinate(restored.employee->getEmployeeId());
                }
            }
        }
        }, "Отмена удаления сотрудника");
    }

    removeEmployeeFromDepartment(record.employee->getDepartmentId(), employeeId);

    employees.data().erase(employees.data().begin() + static_cast<std::ptrdiff_t>(it->second));
    employeeIndex.erase(it);

    for (std::size_t idx = 0; idx < employees.size(); ++idx) {
        employeeIndex[employees[idx].employee->getEmployeeId()] = idx;
    }

    // Удаляем сотрудника из списков подчиненных менеджеров
    for (auto& entry : employees.data()) {
        if (auto manager = std::dynamic_pointer_cast<Manager>(entry.employee)) {
            if (manager->hasSubordinate(employeeId)) {
                manager->removeSubordinate(employeeId);
            }
        }
    }

    return true;
}

bool DataManager::updateEmployeeDepartment(int employeeId, int newDepartmentId) {
    auto* record = findEmployeeRecord(employeeId);
    if (!record) {
        return false;
    }
    if (!findDepartment(newDepartmentId)) {
        std::cerr << "Отдел с ID " << newDepartmentId << " не найден." << std::endl;
        return false;
    }
    const int oldDepartmentId = record->employee->getDepartmentId();

    if (!undoInProgress) {
        pushUndo([this, employeeId, oldDepartmentId]() {
        updateEmployeeDepartment(employeeId, oldDepartmentId);
        }, "Отмена изменения отдела сотрудника");
    }

    removeEmployeeFromDepartment(oldDepartmentId, employeeId);
    record->employee->setDepartmentId(newDepartmentId);
    ensureDepartmentContainsEmployee(newDepartmentId, employeeId);
    return true;
}

bool DataManager::updateEmployeeSalary(int employeeId, double newSalary) {
    auto* record = findEmployeeRecord(employeeId);
    if (!record) {
        return false;
    }
    const double oldSalary = record->employee->getSalary();

    if (!undoInProgress) {
        pushUndo([this, employeeId, oldSalary]() {
        updateEmployeeSalary(employeeId, oldSalary);
        }, "Отмена изменения заработной платы");
    }

    record->employee->setSalary(newSalary);
    return true;
}

bool DataManager::updateEmployeePosition(int employeeId, int newPositionId) {
    auto* record = findEmployeeRecord(employeeId);
    if (!record) {
        return false;
    }

    auto worker = std::dynamic_pointer_cast<Worker>(record->employee);
    if (!worker) {
        return false;
    }
    if (!findPosition(newPositionId)) {
        std::cerr << "Должность с ID " << newPositionId << " не найдена." << std::endl;
        return false;
    }
    const int oldPositionId = worker->getPositionId();

    if (!undoInProgress) {
        pushUndo([this, employeeId, oldPositionId]() {
        updateEmployeePosition(employeeId, oldPositionId);
        }, "Отмена изменения должности");
    }

    worker->setPositionId(newPositionId);
    return true;
}

bool DataManager::updateEmployeeBonus(int employeeId, double newBonus) {
    auto* record = findEmployeeRecord(employeeId);
    if (!record) {
        return false;
    }

    auto worker = std::dynamic_pointer_cast<Worker>(record->employee);
    if (!worker) {
        return false;
    }
    const double oldBonus = worker->getBonus();

    if (!undoInProgress) {
        pushUndo([this, employeeId, oldBonus]() {
        updateEmployeeBonus(employeeId, oldBonus);
        }, "Отмена изменения премии");
    }

    worker->setBonus(newBonus);
    return true;
}

bool DataManager::updateEmployeeName(int employeeId, const std::string& newFirstName, const std::string& newLastName) {
    auto* record = findEmployeeRecord(employeeId);
    if (!record) {
        return false;
    }
    const std::string oldFirst = record->employee->getFirstName();
    const std::string oldLast = record->employee->getLastName();

    if (!undoInProgress) {
        pushUndo([this, employeeId, oldFirst, oldLast]() {
        updateEmployeeName(employeeId, oldFirst, oldLast);
        }, "Отмена изменения ФИО");
    }

    record->employee->setFirstName(newFirstName);
    record->employee->setLastName(newLastName);
    return true;
}

bool DataManager::updateEmployeeHireDate(int employeeId, const HireDate& newHireDate) {
    auto* record = findEmployeeRecord(employeeId);
    if (!record) {
        return false;
    }
    const HireDate oldHireDate = record->hireDate;

    if (!undoInProgress) {
        pushUndo([this, employeeId, oldHireDate]() {
        updateEmployeeHireDate(employeeId, oldHireDate);
        }, "Отмена изменения даты найма");
    }

    record->hireDate = newHireDate;
    return true;
}

int DataManager::addDepartment(const std::string& name, int managerId) {
    const int newId = generateDepartmentId();
    Department department(newId, name, managerId);
    departments.add(department);
    departmentIndex[newId] = departments.size() - 1;

    if (!undoInProgress) {
        pushUndo([this, newId]() {
        removeDepartment(newId);
        }, "Отмена добавления отдела");
    }

    return newId;
}

bool DataManager::removeDepartment(int departmentId) {
    const auto it = departmentIndex.find(departmentId);
    if (it == departmentIndex.end()) {
        return false;
    }

    Department department = departments.data().at(it->second);

    if (!department.getEmployees().empty()) {
        std::cerr << "Невозможно удалить отдел: в нем есть сотрудники" << std::endl;
        return false;
    }

    if (!undoInProgress) {
        pushUndo([this, department]() {
        departments.add(department);
        departmentIndex[department.getDepartmentId()] = departments.size() - 1;
        }, "Отмена удаления отдела");
    }

    departments.data().erase(departments.data().begin() + static_cast<std::ptrdiff_t>(it->second));
    departmentIndex.erase(it);
    for (std::size_t idx = 0; idx < departments.size(); ++idx) {
        departmentIndex[departments[idx].getDepartmentId()] = idx;
    }
    return true;
}

bool DataManager::updateDepartmentName(int departmentId, const std::string& newName) {
    auto* department = findDepartment(departmentId);
    if (!department) {
        return false;
    }
    const std::string oldName = department->getDepartmentName();

    if (!undoInProgress) {
        pushUndo([this, departmentId, oldName]() {
        updateDepartmentName(departmentId, oldName);
        }, "Отмена переименования отдела");
    }

    department->setDepartmentName(newName);
    return true;
}

bool DataManager::updateDepartmentManager(int departmentId, int managerId) {
    auto* department = findDepartment(departmentId);
    if (!department) {
        return false;
    }
    if (managerId != 0 && !findEmployeeRecord(managerId)) {
        std::cerr << "Сотрудник с ID " << managerId << " не найден." << std::endl;
        return false;
    }
    const int oldManager = department->getManagerId();

    if (!undoInProgress) {
        pushUndo([this, departmentId, oldManager]() {
        updateDepartmentManager(departmentId, oldManager);
        }, "Отмена назначения руководителя");
    }

    department->setManagerId(managerId);
    return true;
}

int DataManager::addPosition(const std::string& name, int hoursPerWeek) {
    const int newId = generatePositionId();
    Position position(newId, name, hoursPerWeek);
    positions.add(position);
    positionIndex[newId] = positions.size() - 1;

    if (!undoInProgress) {
        pushUndo([this, newId]() {
        removePosition(newId);
        }, "Отмена добавления должности");
    }

    return newId;
}

bool DataManager::removePosition(int positionId) {
    const auto it = positionIndex.find(positionId);
    if (it == positionIndex.end()) {
        return false;
    }

    for (const auto& record : employees.data()) {
        if (auto worker = std::dynamic_pointer_cast<Worker>(record.employee)) {
            if (worker->getPositionId() == positionId) {
                std::cerr << "Невозможно удалить должность: есть сотрудники на этой должности" << std::endl;
                return false;
            }
        }
    }

    Position position = positions.data().at(it->second);

    if (!undoInProgress) {
        pushUndo([this, position]() {
        positions.add(position);
        positionIndex[position.getPositionId()] = positions.size() - 1;
        }, "Отмена удаления должности");
    }

    positions.data().erase(positions.data().begin() + static_cast<std::ptrdiff_t>(it->second));
    positionIndex.erase(it);
    for (std::size_t idx = 0; idx < positions.size(); ++idx) {
        positionIndex[positions[idx].getPositionId()] = idx;
    }
    return true;
}

bool DataManager::updatePositionName(int positionId, const std::string& newName) {
    auto* position = findPosition(positionId);
    if (!position) {
        return false;
    }
    const std::string oldName = position->getPositionName();

    if (!undoInProgress) {
        pushUndo([this, positionId, oldName]() {
        updatePositionName(positionId, oldName);
        }, "Отмена переименования должности");
    }

    position->setPositionName(newName);
    return true;
}

bool DataManager::updatePositionHours(int positionId, int hoursPerWeek) {
    auto* position = findPosition(positionId);
    if (!position) {
        return false;
    }
    const int oldHours = position->getWorkHoursPerWeek();

    if (!undoInProgress) {
        pushUndo([this, positionId, oldHours]() {
        updatePositionHours(positionId, oldHours);
        }, "Отмена изменения трудоемкости должности");
    }

    position->setWorkHoursPerWeek(hoursPerWeek);
    return true;
}

std::vector<EmployeeRecord> DataManager::findEmployees(const EmployeeSearchFilter& filter) const {
    std::vector<EmployeeRecord> result;
    std::copy_if(employees.begin(), employees.end(), std::back_inserter(result),
                 [&filter](const EmployeeRecord& record) {
                     const auto& employee = record.employee;
                     if (filter.useDepartmentId && employee->getDepartmentId() != filter.departmentId) {
                         return false;
                     }
                     if (filter.useMinSalary && employee->getSalary() < filter.minSalary) {
                         return false;
                     }
                     if (filter.useMaxSalary && employee->getSalary() > filter.maxSalary) {
                         return false;
                     }
                     if (filter.useNameFragment) {
                         const std::string target = filter.nameFragment;
                         const auto fullName = employee->getFullName();
                         if (fullName.find(target) == std::string::npos) {
                             return false;
                         }
                     }
                     if (filter.usePositionId) {
                         const auto worker = std::dynamic_pointer_cast<Worker>(employee);
                         if (!worker || worker->getPositionId() != filter.positionId) {
                             return false;
                         }
                     }
                     return true;
                 });
    return result;
}

std::vector<EmployeeRecord> DataManager::sortEmployees(EmployeeSortKey key, bool descending) const {
    auto sorted = employees.data();
    auto comparator = [key, descending](const EmployeeRecord& lhs, const EmployeeRecord& rhs) {
        auto compareAscending = [&]() {
            switch (key) {
            case EmployeeSortKey::ById:
                return lhs.employee->getEmployeeId() < rhs.employee->getEmployeeId();
            case EmployeeSortKey::ByDepartment:
                if (lhs.employee->getDepartmentId() == rhs.employee->getDepartmentId()) {
                    return lhs.employee->getEmployeeId() < rhs.employee->getEmployeeId();
                }
                return lhs.employee->getDepartmentId() < rhs.employee->getDepartmentId();
            case EmployeeSortKey::BySalary:
                if (lhs.employee->getSalary() == rhs.employee->getSalary()) {
                    return lhs.employee->getEmployeeId() < rhs.employee->getEmployeeId();
                }
                return lhs.employee->getSalary() < rhs.employee->getSalary();
            case EmployeeSortKey::ByLastName:
                if (lhs.employee->getLastName() == rhs.employee->getLastName()) {
                    return lhs.employee->getFirstName() < rhs.employee->getFirstName();
                }
                return lhs.employee->getLastName() < rhs.employee->getLastName();
            case EmployeeSortKey::ByHireDate:
                if (lhs.hireDate.getYear() != rhs.hireDate.getYear()) {
                    return lhs.hireDate.getYear() < rhs.hireDate.getYear();
                }
                if (lhs.hireDate.getMonth() != rhs.hireDate.getMonth()) {
                    return lhs.hireDate.getMonth() < rhs.hireDate.getMonth();
                }
                if (lhs.hireDate.getDay() != rhs.hireDate.getDay()) {
                    return lhs.hireDate.getDay() < rhs.hireDate.getDay();
                }
                return lhs.employee->getEmployeeId() < rhs.employee->getEmployeeId();
            default:
                return lhs.employee->getEmployeeId() < rhs.employee->getEmployeeId();
            }
        };
        const bool asc = compareAscending();
        return descending ? !asc : asc;
    };

    std::stable_sort(sorted.begin(), sorted.end(), comparator);
    return sorted;
}

bool DataManager::canUndo() const {
    return !undoStack.empty();
}

bool DataManager::undoLastAction() {
    if (!canUndo()) {
        return false;
    }
    const UndoCommand command = undoStack.back();
    undoStack.pop_back();
    undoInProgress = true;
    command.undo();
    undoInProgress = false;
    std::cout << "Отменено действие: " << command.description << std::endl;
    return true;
}

std::string DataManager::getLastUndoDescription() const {
    if (undoStack.empty()) {
        return {};
    }
    return undoStack.back().description;
}

void DataManager::loadEmployees() {
    std::ifstream file(employeesPath);
    if (!file.is_open()) {
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '#') {
            continue;
        }
        const auto parts = split(line, ';');
        if (parts.size() < 6) {
            std::cerr << "Некорректная строка в employees.txt: " << line << std::endl;
            continue;
        }

        try {
            const int id = std::stoi(parts[0]);
            const std::string type = parts[1];
            const std::string firstName = parts[2];
            const std::string lastName = parts[3];
            const int departmentId = std::stoi(parts[4]);
            const double salary = std::stod(parts[5]);

            std::shared_ptr<Employee> employeePtr;

            if (type == "WORKER") {
                if (parts.size() < 8) {
                    std::cerr << "Недостаточно данных для работника: " << line << std::endl;
                    continue;
                }
                const int positionId = std::stoi(parts[6]);
                const double bonus = std::stod(parts[7]);
                employeePtr = std::make_shared<Worker>(id, firstName, lastName, departmentId, salary, positionId, bonus);
            } else if (type == "MANAGER") {
                std::vector<int> subordinates;
                if (parts.size() >= 7 && !parts[6].empty()) {
                    const auto subordinateTokens = split(parts[6], ',');
                    for (const auto& token : subordinateTokens) {
                        if (!token.empty()) {
                            subordinates.push_back(std::stoi(token));
                        }
                    }
                }
                employeePtr = std::make_shared<Manager>(id, firstName, lastName, departmentId, salary, subordinates);
            } else {
                std::cerr << "Неизвестный тип сотрудника: " << type << std::endl;
                continue;
            }

            EmployeeRecord record{employeePtr, HireDate(id, 1, 1, 2000, 9, 0)};
            employees.add(record);
            registerEmployee(record);
            ensureDepartmentContainsEmployee(departmentId, id);
            nextEmployeeId = std::max(nextEmployeeId, id + 1);
        } catch (const std::exception& ex) {
            std::cerr << "Ошибка чтения сотрудника: " << ex.what() << std::endl;
        }
    }
}

void DataManager::loadDepartments() {
    std::ifstream file(departmentsPath);
    if (!file.is_open()) {
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '#') {
            continue;
        }
        const auto parts = split(line, ';');
        if (parts.size() < 3) {
            std::cerr << "Некорректная строка в departments.txt: " << line << std::endl;
            continue;
        }

        try {
            const int id = std::stoi(parts[0]);
            const std::string name = parts[1];
            const int managerId = std::stoi(parts[2]);

            Department department(id, name, managerId);
            if (parts.size() >= 4 && !parts[3].empty()) {
                const auto employeeTokens = split(parts[3], ',');
                for (const auto& token : employeeTokens) {
                    if (!token.empty()) {
                        department.addEmployee(std::stoi(token));
                    }
                }
            }

            departments.add(department);
            departmentIndex[id] = departments.size() - 1;
            nextDepartmentId = std::max(nextDepartmentId, id + 1);
        } catch (const std::exception& ex) {
            std::cerr << "Ошибка чтения отдела: " << ex.what() << std::endl;
        }
    }
}

void DataManager::loadPositions() {
    std::ifstream file(positionsPath);
    if (!file.is_open()) {
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '#') {
            continue;
        }
        const auto parts = split(line, ';');
        if (parts.size() < 3) {
            std::cerr << "Некорректная строка в positions.txt: " << line << std::endl;
            continue;
        }
        try {
            const int id = std::stoi(parts[0]);
            const std::string name = parts[1];
            const int hours = std::stoi(parts[2]);

            positions.add(Position(id, name, hours));
            positionIndex[id] = positions.size() - 1;
            nextPositionId = std::max(nextPositionId, id + 1);
        } catch (const std::exception& ex) {
            std::cerr << "Ошибка чтения должности: " << ex.what() << std::endl;
        }
    }
}

void DataManager::loadHireDates() {
    std::ifstream file(hiresPath);
    if (!file.is_open()) {
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '#') {
            continue;
        }
        const auto parts = split(line, ';');
        if (parts.size() < 6) {
            std::cerr << "Некорректная строка в hires.txt: " << line << std::endl;
            continue;
        }

        try {
            const int employeeId = std::stoi(parts[0]);
            const int day = std::stoi(parts[1]);
            const int month = std::stoi(parts[2]);
            const int year = std::stoi(parts[3]);
            const int hour = std::stoi(parts[4]);
            const int minute = std::stoi(parts[5]);

            auto* record = findEmployeeRecord(employeeId);
            if (record) {
                record->hireDate = HireDate(employeeId, day, month, year, hour, minute);
            }
        } catch (const std::exception& ex) {
            std::cerr << "Ошибка чтения даты найма: " << ex.what() << std::endl;
        }
    }
}

void DataManager::saveEmployees() const {
    std::ofstream file(employeesPath, std::ios::trunc);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл сотрудников для записи");
    }

    for (const auto& record : employees.data()) {
        const auto& employee = record.employee;
        if (std::dynamic_pointer_cast<Worker>(employee)) {
            const auto worker = std::dynamic_pointer_cast<Worker>(employee);
            file << employee->getEmployeeId() << ";WORKER;"
                 << employee->getFirstName() << ';'
                 << employee->getLastName() << ';'
                 << employee->getDepartmentId() << ';'
                 << employee->getSalary() << ';'
                 << worker->getPositionId() << ';'
                 << worker->getBonus() << '\n';
        } else if (std::dynamic_pointer_cast<Manager>(employee)) {
            const auto manager = std::dynamic_pointer_cast<Manager>(employee);
            file << employee->getEmployeeId() << ";MANAGER;"
                 << employee->getFirstName() << ';'
                 << employee->getLastName() << ';'
                 << employee->getDepartmentId() << ';'
                 << employee->getSalary() << ';';
            const auto subs = manager->getSubordinates();
            for (std::size_t i = 0; i < subs.size(); ++i) {
                file << subs[i];
                if (i + 1 < subs.size()) {
                    file << ',';
                }
            }
            file << '\n';
        }
    }
}

void DataManager::saveDepartments() const {
    std::ofstream file(departmentsPath, std::ios::trunc);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл отделов для записи");
    }

    for (const auto& department : departments.data()) {
        file << department.getDepartmentId() << ';'
             << department.getDepartmentName() << ';'
             << department.getManagerId() << ';';
        const auto employeesList = department.getEmployees();
        for (std::size_t i = 0; i < employeesList.size(); ++i) {
            file << employeesList[i];
            if (i + 1 < employeesList.size()) {
                file << ',';
            }
        }
        file << '\n';
    }
}

void DataManager::savePositions() const {
    std::ofstream file(positionsPath, std::ios::trunc);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл должностей для записи");
    }

    for (const auto& position : positions.data()) {
        file << position.getPositionId() << ';'
             << position.getPositionName() << ';'
             << position.getWorkHoursPerWeek() << '\n';
    }
}

void DataManager::saveHireDates() const {
    std::ofstream file(hiresPath, std::ios::trunc);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл дат приема на работу для записи");
    }

    for (const auto& record : employees.data()) {
        const auto& hire = record.hireDate;
        file << record.employee->getEmployeeId() << ';'
             << hire.getDay() << ';'
             << hire.getMonth() << ';'
             << hire.getYear() << ';'
             << hire.getHour() << ';'
             << hire.getMinute() << '\n';
    }
}

std::shared_ptr<Employee> DataManager::cloneEmployee(const Employee& source) const {
    if (const auto worker = dynamic_cast<const Worker*>(&source)) {
        return std::make_shared<Worker>(worker->getEmployeeId(),
                                        worker->getFirstName(),
                                        worker->getLastName(),
                                        worker->getDepartmentId(),
                                        worker->getSalary(),
                                        worker->getPositionId(),
                                        worker->getBonus());
    }
    if (const auto manager = dynamic_cast<const Manager*>(&source)) {
        return std::make_shared<Manager>(manager->getEmployeeId(),
                                         manager->getFirstName(),
                                         manager->getLastName(),
                                         manager->getDepartmentId(),
                                         manager->getSalary(),
                                         manager->getSubordinates());
    }
    return std::make_shared<Employee>(source.getEmployeeId(),
                                      source.getFirstName(),
                                      source.getLastName(),
                                      source.getDepartmentId(),
                                      source.getSalary());
}

EmployeeRecord* DataManager::findEmployeeRecord(int employeeId) {
    const auto it = employeeIndex.find(employeeId);
    if (it == employeeIndex.end()) {
        return nullptr;
    }
    return &employees.data().at(it->second);
}

const EmployeeRecord* DataManager::findEmployeeRecord(int employeeId) const {
    const auto it = employeeIndex.find(employeeId);
    if (it == employeeIndex.end()) {
        return nullptr;
    }
    return &employees.data().at(it->second);
}

Department* DataManager::findDepartment(int departmentId) {
    const auto it = departmentIndex.find(departmentId);
    if (it == departmentIndex.end()) {
        return nullptr;
    }
    return &departments.data().at(it->second);
}

const Department* DataManager::findDepartment(int departmentId) const {
    const auto it = departmentIndex.find(departmentId);
    if (it == departmentIndex.end()) {
        return nullptr;
    }
    return &departments.data().at(it->second);
}

Position* DataManager::findPosition(int positionId) {
    const auto it = positionIndex.find(positionId);
    if (it == positionIndex.end()) {
        return nullptr;
    }
    return &positions.data().at(it->second);
}

const Position* DataManager::findPosition(int positionId) const {
    const auto it = positionIndex.find(positionId);
    if (it == positionIndex.end()) {
        return nullptr;
    }
    return &positions.data().at(it->second);
}

void DataManager::registerEmployee(const EmployeeRecord& record) {
    const std::size_t index = employees.size() - 1;
    employeeIndex[record.employee->getEmployeeId()] = index;
}

void DataManager::unregisterEmployee(int employeeId) {
    employeeIndex.erase(employeeId);
}

void DataManager::ensureDepartmentContainsEmployee(int departmentId, int employeeId) {
    if (auto* department = findDepartment(departmentId)) {
        if (!department->hasEmployee(employeeId)) {
            department->addEmployee(employeeId);
        }
    }
}

void DataManager::removeEmployeeFromDepartment(int departmentId, int employeeId) {
    if (auto* department = findDepartment(departmentId)) {
        department->removeEmployee(employeeId);
    }
}

void DataManager::pushUndo(std::function<void()> undoAction, const std::string& description) {
    if (undoInProgress) {
        return;
    }
    undoStack.push_back({std::move(undoAction), description});
}

int DataManager::generateEmployeeId() {
    return nextEmployeeId++;
}

int DataManager::generateDepartmentId() {
    return nextDepartmentId++;
}

int DataManager::generatePositionId() {
    return nextPositionId++;
}

