#include "../include/FileException.h"

FileException::FileException(int code, const std::string& message) noexcept
    : Exception(code, message) {}
