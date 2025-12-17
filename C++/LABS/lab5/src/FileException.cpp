#include "../include/FileException.h"

FileException::FileException(int errorCode, const std::string& errorMessage) noexcept
    : Exception(errorCode, errorMessage) {}
