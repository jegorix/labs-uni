//
// Лаба 5: иерархия исключений для обработки ошибок ввода, файлов и контейнеров.
//

#ifndef LAB4_EXCEPTIONS_H
#define LAB4_EXCEPTIONS_H

#include <exception>
#include <string>

// Базовый класс всех пользовательских исключений
class Exception : public std::exception {
protected:
    int code;           // код ошибки (см. диапазоны ниже)
    std::string msg;    // текстовое описание

public:
    // Диапазоны кодов:
    // 0  -  50  : ошибки ввода в консоль
    // 50 - 100  : ошибки при работе с файлами
    // 100- 150  : ошибки, связанные с контейнерами
    Exception(int code, const std::string& message) noexcept
        : code(code), msg(message) {}

    int getCode() const noexcept { return code; }

    const char* what() const noexcept override {
        return msg.c_str();
    }
};

// Ошибки ввода пользователя
class InputException : public Exception {
public:
    explicit InputException(int code, const std::string& message) noexcept
        : Exception(code, message) {}
};

// Ошибки при работе с файлами
class FileException : public Exception {
public:
    explicit FileException(int code, const std::string& message) noexcept
        : Exception(code, message) {}
};

// Ошибки, связанные с контейнерами (например, выход за границы, пустой контейнер и т.п.)
class ContainerException : public Exception {
public:
    explicit ContainerException(int code, const std::string& message) noexcept
        : Exception(code, message) {}
};

#endif // LAB4_EXCEPTIONS_H


