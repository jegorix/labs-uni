#include "../include/InputException.h"

InputException::InputException(int code, const std::string& message) noexcept
    : Exception(code, message) {}
