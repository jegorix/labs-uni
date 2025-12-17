#pragma once

#include "Exception.h"

// Ошибки, связанные с контейнерами (например, выход за границы, пустой контейнер и т.п.)
class ContainerException : public Exception {
public:
    explicit ContainerException(int code, const std::string& message) noexcept;
};
