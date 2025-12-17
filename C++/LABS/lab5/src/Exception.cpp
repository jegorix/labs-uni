#include "../include/Exception.h"

Exception::Exception(int errorCode, const std::string& errorMessage) noexcept
    : code(errorCode), message(errorMessage) {}

int Exception::getCode() const noexcept {
    return code;
}

const char* Exception::what() const noexcept {
    return message.c_str();
}
