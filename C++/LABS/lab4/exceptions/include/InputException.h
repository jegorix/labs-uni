#pragma once

#include "Exception.h"

// Ошибки ввода пользователя
class InputException : public Exception {
public:
    explicit InputException(int code, const std::string& message) noexcept;
};
