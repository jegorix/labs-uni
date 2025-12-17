#include "../include/FileException.hpp"

FileException::FileException(int errorCode, const std::string& errorMessage)
    : Exception(errorCode, errorMessage) {}



