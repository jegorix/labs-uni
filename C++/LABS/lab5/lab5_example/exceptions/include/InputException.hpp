#pragma once
#include "Exception.hpp"

class InputException : public Exception {
public:
    InputException(int errorCode, const std::string& errorMessage);
    ~InputException() = default;
};



