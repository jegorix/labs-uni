#include "../include/InputException.hpp"

InputException::InputException(int errorCode, const std::string& errorMessage)
    : Exception(errorCode, errorMessage) {}



