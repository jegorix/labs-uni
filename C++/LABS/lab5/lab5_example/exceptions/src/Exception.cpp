#include "../include/Exception.hpp"

Exception::Exception(int errorCode, const std::string& errorMessage) 
    : code(errorCode), message(errorMessage) {}

int Exception::getCode() const {
    return code;
}

const char* Exception::what() const noexcept {
    return message.c_str();
}



