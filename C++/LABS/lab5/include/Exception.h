#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

// Базовый класс для пользовательских исключений.
class Exception : public std::exception {
protected:
    int code;              // Код ошибки (для группировки типов ошибок)
    std::string message;   // Человеко-читаемое описание

public:
    Exception(int errorCode, const std::string& errorMessage) noexcept;
    ~Exception() override = default;

    int getCode() const noexcept;
    const char* what() const noexcept override;
};

#endif // EXCEPTION_H
