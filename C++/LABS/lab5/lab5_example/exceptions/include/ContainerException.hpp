#pragma once
#include "Exception.hpp"

class ContainerException : public Exception {
public:
    ContainerException(int errorCode, const std::string& errorMessage);
    ~ContainerException() = default;
};



