#include "../include/Exception.h"

Exception::Exception(int code, const std::string& message) noexcept
    : code(code), msg(message) {}

int Exception::getCode() const noexcept {
    return code;
}

const char* Exception::what() const noexcept {
    return msg.c_str();
}
