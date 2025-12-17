#include "../include/ContainerException.h"

ContainerException::ContainerException(int code, const std::string& message) noexcept
    : Exception(code, message) {}
