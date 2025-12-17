#pragma once

#include "Exception.h"

// Ошибки при работе с файлами
class FileException : public Exception {
public:
    explicit FileException(int code, const std::string& message) noexcept;
};
