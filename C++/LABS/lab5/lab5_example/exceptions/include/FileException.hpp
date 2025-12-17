#pragma once
#include "Exception.hpp"

class FileException : public Exception {
public:
    FileException(int errorCode, const std::string& errorMessage);
    ~FileException() = default;
};



