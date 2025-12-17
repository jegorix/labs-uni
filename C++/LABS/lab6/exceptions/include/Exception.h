#pragma once

#include <exception>
#include <string>

// Базовый класс всех пользовательских исключений
class Exception : public std::exception {
protected:
    int code;           // код ошибки
    std::string msg;    // текстовое описание

public:
    Exception(int code, const std::string& message) noexcept;
    int getCode() const noexcept;
    const char* what() const noexcept override;
};
