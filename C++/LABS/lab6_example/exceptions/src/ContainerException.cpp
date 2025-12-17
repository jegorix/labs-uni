#include "../include/ContainerException.hpp"

ContainerException::ContainerException(int errorCode, const std::string& errorMessage)
    : Exception(errorCode, errorMessage) {}



