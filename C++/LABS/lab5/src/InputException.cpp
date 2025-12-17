#include "../include/InputException.h"

InputException::InputException(int errorCode, const std::string& errorMessage) noexcept
    : Exception(errorCode, errorMessage) {}
