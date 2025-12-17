#include "Exception.h"
#include <sstream>

Exception::Exception(const std::string& msg)
    : message(msg), fileName(""), lineNumber(0) {}

Exception::Exception(const std::string& msg, const std::string& file, int line)
    : message(msg), fileName(file), lineNumber(line) {}


const char* Exception::what() const noexcept
{
    return message.c_str();
}

std::string Exception::getMessage() const
{
    return message;
}

std::string Exception::getFileName() const
{
    return fileName;
}

int Exception::getLineNumber() const
{
    return lineNumber;
}

std::string Exception::getType() const
{
    return "Base Exception";
}

std::string Exception::getFullInfo() const
{
    std::ostringstream oss;

    oss << "[" << getType() << "]: " << message;
    
    if (!fileName.empty()) {
        oss << " (File: " << fileName;
        if (lineNumber > 0) {
            oss << ", Line: " << lineNumber;
        }
        oss << ")";


        return oss.str();
}