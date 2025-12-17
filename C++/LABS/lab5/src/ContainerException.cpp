#include "../include/ContainerException.h"

ContainerException::ContainerException(int errorCode, const std::string& errorMessage) noexcept
    : Exception(errorCode, errorMessage) {}
