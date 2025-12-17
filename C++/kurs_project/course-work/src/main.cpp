#include "../include/DataManager.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

namespace {

std::string detectDataDirectory() {
    const std::vector<std::string> candidates = {
        "data",
        "../data",
        "../../data",
        "../../../data"
    };
    for (const auto& candidate : candidates) {
        std::ifstream test(candidate + "/employees.txt");
        if (test.good()) {
            return candidate;
        }
    }
    return "data";
}

void pause() {
    std::cout << "Нажмите Enter для продолжения...";
    std::string dummy;
    std::getline(std::cin, dummy);
}

int readInt(const std::string& prompt, int defaultValue = 0, bool allowSkip = false) {
    while (true) {
        std::cout << prompt;
        std::string line;
        std::getline(std::cin, line);
        if (allowSkip && line.empty()) {
            return defaultValue;
        }
        std::stringstream ss(line);
        int value;
        if (ss >> value) {
            return value;
        }
        std::cout << "Некорректное число, попробуйте снова.\n";
    }
}

double readDouble(const std::string& prompt, double defaultValue = 0.0, bool allowSkip = false) {
    while (true) {
        std::cout << prompt;
        std::string line;
        std::getline(std::cin, line);
        if (allowSkip && line.empty()) {
            return defaultValue;
        }
        std::stringstream ss(line);
        double value;
        if (ss >> value) {
            return value;
        }
        std::cout << "Некорректное число, попробуйте снова.\n";
    }
}

HireDate readHireDate(int employeeId) {
    while (true) {
        int day = readInt("День приема (1-31): ");
        int month = readInt("Месяц приема (1-12): ");
        int year = readInt("Год приема (например, 2021): ");
        int hour = readInt("Час начала работы (0-23): ");
        int minute = readInt("Минута начала работы (0-59): ");
        try {
            return HireDate(employeeId, day, month, year, hour, minute);
        } catch (const std::exception& ex) {
            std::cout << "Ошибка: " << ex.what() << ". Повторите ввод даты.\n";
        }
    }
}

void showEmployee(const EmployeeRecord& record, const DataManager& manager) {
    const auto& employee = record.employee;
    std::cout << "ID: " << employee->getEmployeeId()
              << " | ФИО: " << employee->getFullName()
              << " | Отдел #" << employee->getDepartmentId()
              << " | Оклад: " << std::fixed << std::setprecision(2) << employee->getSalary();

    if (auto worker = std::dynamic_pointer_cast<Worker>(employee)) {
        std::cout << " | Должность #" << worker->getPositionId()
                  << " | Премия: " << worker->getBonus();
    } else if (auto managerPtr = std::dynamic_pointer_cast<Manager>(employee)) {
        std::cout << " | Менеджер (" << managerPtr->getSubordinatesCount() << " подчиненных)";
    }

    std::cout << " | Принят: " << record.hireDate.getFullDateTimeString() << '\n';
}

void listEmployees(DataManager& manager) {
    std::cout << "\nСортировка сотрудников:\n"
              << "1. По ID\n"
              << "2. По отделу\n"
              << "3. По зарплате\n"
              << "4. По фамилии\n"
              << "5. По дате найма\n";
    int choice = readInt("Выберите пункт: ", 1);
    int direction = readInt("Порядок (0 - по возрастанию, 1 - по убыванию): ", 0);

    EmployeeSortKey key = EmployeeSortKey::ById;
    switch (choice) {
    case 2:
        key = EmployeeSortKey::ByDepartment;
        break;
    case 3:
        key = EmployeeSortKey::BySalary;
        break;
    case 4:
        key = EmployeeSortKey::ByLastName;
        break;
    case 5:
        key = EmployeeSortKey::ByHireDate;
        break;
    default:
        key = EmployeeSortKey::ById;
        break;
    }

    const auto sorted = manager.sortEmployees(key, direction == 1);
    std::cout << "\n--- Список сотрудников ---\n";
    for (const auto& record : sorted) {
        showEmployee(record, manager);
    }
}

void addEmployeeMenu(DataManager& manager) {
    std::cout << "\nДобавление сотрудника\n"
              << "1. Работник\n"
              << "2. Менеджер\n";
    const int choice = readInt("Ваш выбор: ", 1);

    std::string firstName;
    std::string lastName;
    std::cout << "Имя: ";
    std::getline(std::cin, firstName);
    std::cout << "Фамилия: ";
    std::getline(std::cin, lastName);

    const int departmentId = readInt("Номер отдела: ");
    const double salary = readDouble("Оклад: ");

    HireDate hireDate(0, 1, 1, 2000, 9, 0);

    if (choice == 1) {
        const int positionId = readInt("Номер должности: ");
        const double bonus = readDouble("Премия: ");
        hireDate = readHireDate(0);
        try {
            const int newId = manager.addWorker(firstName, lastName, departmentId, salary, positionId, bonus, hireDate);
            std::cout << "Добавлен работник с ID " << newId << '\n';
        } catch (const std::exception& ex) {
            std::cout << "Не удалось добавить работника: " << ex.what() << '\n';
        }
    } else {
        std::cout << "Введите номера подчиненных через пробел (пустая строка - нет): ";
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::vector<int> subordinates;
        int subordinateId;
        while (ss >> subordinateId) {
            subordinates.push_back(subordinateId);
        }
        hireDate = readHireDate(0);
        try {
            const int newId = manager.addManager(firstName, lastName, departmentId, salary, subordinates, hireDate);
            std::cout << "Добавлен менеджер с ID " << newId << '\n';
        } catch (const std::exception& ex) {
            std::cout << "Не удалось добавить менеджера: " << ex.what() << '\n';
        }
    }
}

void editEmployeeMenu(DataManager& manager) {
    const int employeeId = readInt("Введите ID сотрудника: ");
    auto& employees = manager.getEmployees();
    auto it = employees.findIf([employeeId](const EmployeeRecord& record) {
        return record.employee->getEmployeeId() == employeeId;
    });
    if (it == employees.end()) {
        std::cout << "Сотрудник не найден.\n";
        return;
    }

    std::cout << "\nРедактирование сотрудника #" << employeeId << "\n"
              << "1. Изменить ФИО\n"
              << "2. Изменить отдел\n"
              << "3. Изменить зарплату\n"
              << "4. Изменить должность (для работника)\n"
              << "5. Изменить премию (для работника)\n"
              << "6. Изменить дату приема\n";

    const int choice = readInt("Ваш выбор: ");
    switch (choice) {
    case 1: {
        std::string firstName;
        std::string lastName;
        std::cout << "Новое имя: ";
        std::getline(std::cin, firstName);
        std::cout << "Новая фамилия: ";
        std::getline(std::cin, lastName);
        if (manager.updateEmployeeName(employeeId, firstName, lastName)) {
            std::cout << "ФИО обновлено.\n";
        }
        break;
    }
    case 2: {
        const int departmentId = readInt("Новый отдел: ");
        if (manager.updateEmployeeDepartment(employeeId, departmentId)) {
            std::cout << "Отдел обновлен.\n";
        }
        break;
    }
    case 3: {
        const double salary = readDouble("Новая зарплата: ");
        if (manager.updateEmployeeSalary(employeeId, salary)) {
            std::cout << "Зарплата обновлена.\n";
        }
        break;
    }
    case 4: {
        const int positionId = readInt("Новая должность: ");
        if (manager.updateEmployeePosition(employeeId, positionId)) {
            std::cout << "Должность обновлена.\n";
        } else {
            std::cout << "Изменение должности возможно только для работника.\n";
        }
        break;
    }
    case 5: {
        const double bonus = readDouble("Новая премия: ");
        if (manager.updateEmployeeBonus(employeeId, bonus)) {
            std::cout << "Премия обновлена.\n";
        } else {
            std::cout << "Изменение премии возможно только для работника.\n";
        }
        break;
    }
    case 6: {
        HireDate hireDate = readHireDate(employeeId);
        if (manager.updateEmployeeHireDate(employeeId, hireDate)) {
            std::cout << "Дата приема обновлена.\n";
        }
        break;
    }
    default:
        std::cout << "Неизвестный пункт.\n";
    }
}

void removeEmployeeMenu(DataManager& manager) {
    const int employeeId = readInt("Введите ID сотрудника для удаления: ");
    if (manager.removeEmployee(employeeId)) {
        std::cout << "Сотрудник удален.\n";
    } else {
        std::cout << "Сотрудник не найден.\n";
    }
}

void searchEmployeesMenu(DataManager& manager) {
    EmployeeSearchFilter filter;
    std::cout << "Введите фильтры (пустой ввод - пропустить)\n";
    std::string line;

    std::cout << "Отдел: ";
    std::getline(std::cin, line);
    if (!line.empty()) {
        std::stringstream ss(line);
        int value = 0;
        if (ss >> value) {
            filter.useDepartmentId = true;
            filter.departmentId = value;
        } else {
            std::cout << "Предупреждение: некорректный номер отдела, фильтр не применен.\n";
        }
    }

    std::cout << "Минимальная зарплата: ";
    std::getline(std::cin, line);
    if (!line.empty()) {
        std::stringstream ss(line);
        double value = 0.0;
        if (ss >> value) {
            filter.useMinSalary = true;
            filter.minSalary = value;
        } else {
            std::cout << "Предупреждение: некорректное значение зарплаты, фильтр не применен.\n";
        }
    }

    std::cout << "Максимальная зарплата: ";
    std::getline(std::cin, line);
    if (!line.empty()) {
        std::stringstream ss(line);
        double value = 0.0;
        if (ss >> value) {
            filter.useMaxSalary = true;
            filter.maxSalary = value;
        } else {
            std::cout << "Предупреждение: некорректное значение зарплаты, фильтр не применен.\n";
        }
    }

    std::cout << "Фрагмент ФИО: ";
    std::getline(std::cin, line);
    if (!line.empty()) {
        filter.useNameFragment = true;
        filter.nameFragment = line;
    }

    std::cout << "Должность: ";
    std::getline(std::cin, line);
    if (!line.empty()) {
        std::stringstream ss(line);
        int value = 0;
        if (ss >> value) {
            filter.usePositionId = true;
            filter.positionId = value;
        } else {
            std::cout << "Предупреждение: некорректный номер должности, фильтр не применен.\n";
        }
    }

    const auto found = manager.findEmployees(filter);
    std::cout << "\n--- Найденные сотрудники (" << found.size() << ") ---\n";
    for (const auto& record : found) {
        showEmployee(record, manager);
    }
}

void showDepartments(DataManager& manager) {
    auto& departments = manager.getDepartments();
    departments.insertionSort([](const Department& lhs, const Department& rhs) {
        return lhs.getDepartmentName() < rhs.getDepartmentName();
    });
    std::cout << "\n--- Отделы ---\n";
    for (const auto& department : departments.data()) {
        std::cout << "ID: " << department.getDepartmentId()
                  << " | Название: " << department.getDepartmentName()
                  << " | Руководитель: " << department.getManagerId()
                  << " | Сотрудников: " << department.getEmployeesCount() << '\n';
    }
}

void manageDepartmentsMenu(DataManager& manager) {
    while (true) {
        std::cout << "\nУправление отделами\n"
                  << "1. Показать отделы\n"
                  << "2. Добавить отдел\n"
                  << "3. Переименовать отдел\n"
                  << "4. Назначить руководителя\n"
                  << "5. Удалить отдел\n"
                  << "0. Назад\n";
        const int choice = readInt("Ваш выбор: ");
        if (choice == 0) {
            break;
        }

        switch (choice) {
        case 1:
            showDepartments(manager);
            break;
        case 2: {
            std::string name;
            std::cout << "Название отдела: ";
            std::getline(std::cin, name);
            const int managerId = readInt("ID руководителя: ");
            const int id = manager.addDepartment(name, managerId);
            std::cout << "Добавлен отдел #" << id << '\n';
            break;
        }
        case 3: {
            const int id = readInt("ID отдела: ");
            std::string newName;
            std::cout << "Новое название: ";
            std::getline(std::cin, newName);
            if (manager.updateDepartmentName(id, newName)) {
                std::cout << "Название обновлено.\n";
            } else {
                std::cout << "Отдел не найден.\n";
            }
            break;
        }
        case 4: {
            const int id = readInt("ID отдела: ");
            const int managerId = readInt("Новый руководитель: ");
            if (manager.updateDepartmentManager(id, managerId)) {
                std::cout << "Руководитель назначен.\n";
            } else {
                std::cout << "Отдел не найден.\n";
            }
            break;
        }
        case 5: {
            const int id = readInt("ID отдела: ");
            if (manager.removeDepartment(id)) {
                std::cout << "Отдел удален.\n";
            } else {
                std::cout << "Не удалось удалить отдел.\n";
            }
            break;
        }
        default:
            std::cout << "Неизвестный пункт.\n";
        }
    }
}

void showPositions(DataManager& manager) {
    auto& positions = manager.getPositions();
    positions.insertionSort([](const Position& lhs, const Position& rhs) {
        return lhs.getPositionName() < rhs.getPositionName();
    });
    std::cout << "\n--- Должности ---\n";
    for (const auto& position : positions.data()) {
        std::cout << "ID: " << position.getPositionId()
                  << " | Название: " << position.getPositionName()
                  << " | Часов в неделю: " << position.getWorkHoursPerWeek() << '\n';
    }
}

void managePositionsMenu(DataManager& manager) {
    while (true) {
        std::cout << "\nУправление должностями\n"
                  << "1. Показать должности\n"
                  << "2. Добавить должность\n"
                  << "3. Переименовать должность\n"
                  << "4. Изменить часы\n"
                  << "5. Удалить должность\n"
                  << "0. Назад\n";
        const int choice = readInt("Ваш выбор: ");
        if (choice == 0) {
            break;
        }

        switch (choice) {
        case 1:
            showPositions(manager);
            break;
        case 2: {
            std::string name;
            std::cout << "Название должности: ";
            std::getline(std::cin, name);
            const int hours = readInt("Часы в неделю: ");
            const int id = manager.addPosition(name, hours);
            std::cout << "Добавлена должность #" << id << '\n';
            break;
        }
        case 3: {
            const int id = readInt("ID должности: ");
            std::string newName;
            std::cout << "Новое название: ";
            std::getline(std::cin, newName);
            if (manager.updatePositionName(id, newName)) {
                std::cout << "Название обновлено.\n";
            } else {
                std::cout << "Должность не найдена.\n";
            }
            break;
        }
        case 4: {
            const int id = readInt("ID должности: ");
            const int hours = readInt("Новые часы: ");
            if (manager.updatePositionHours(id, hours)) {
                std::cout << "Рабочее время обновлено.\n";
            } else {
                std::cout << "Должность не найдена.\n";
            }
            break;
        }
        case 5: {
            const int id = readInt("ID должности: ");
            if (manager.removePosition(id)) {
                std::cout << "Должность удалена.\n";
            } else {
                std::cout << "Не удалось удалить должность.\n";
            }
            break;
        }
        default:
            std::cout << "Неизвестный пункт.\n";
        }
    }
}

void showMainMenu() {
    std::cout << "\n--- Главное меню ---\n"
              << "1. Список сотрудников\n"
              << "2. Добавить сотрудника\n"
              << "3. Редактировать сотрудника\n"
              << "4. Удалить сотрудника\n"
              << "5. Поиск сотрудников\n"
              << "6. Управление отделами\n"
              << "7. Управление должностями\n"
              << "8. Отменить последнее действие\n"
              << "9. Сохранить данные\n"
              << "0. Выход\n";
}

} // namespace

int main() {
    try {
        std::locale::global(std::locale("ru_RU.UTF-8"));
    } catch (...) {
        std::locale::global(std::locale(""));
    }
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    try {
        const std::string dataDir = detectDataDirectory();
        DataManager manager(dataDir);
        manager.loadAll();

        bool running = true;
        while (running) {
            showMainMenu();
            const int choice = readInt("Выберите пункт меню: ");
            switch (choice) {
            case 1:
                listEmployees(manager);
                pause();
                break;
            case 2:
                addEmployeeMenu(manager);
                pause();
                break;
            case 3:
                editEmployeeMenu(manager);
                pause();
                break;
            case 4:
                removeEmployeeMenu(manager);
                pause();
                break;
            case 5:
                searchEmployeesMenu(manager);
                pause();
                break;
            case 6:
                manageDepartmentsMenu(manager);
                break;
            case 7:
                managePositionsMenu(manager);
                break;
            case 8:
                if (!manager.undoLastAction()) {
                    std::cout << "Нет действий для отмены.\n";
                }
                pause();
                break;
            case 9:
                manager.saveAll();
                std::cout << "Данные сохранены.\n";
                pause();
                break;
            case 0:
                running = false;
                manager.saveAll();
                std::cout << "Изменения сохранены. Выход.\n";
                break;
            default:
                std::cout << "Неизвестный пункт.\n";
            }
        }
    } catch (const std::exception& ex) {
        std::cerr << "Ошибка: " << ex.what() << '\n';
        return 1;
    }

    return 0;
}

