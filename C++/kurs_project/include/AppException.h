// AppException.h
#ifndef APPEXCEPTION_H
#define APPEXCEPTION_H

#include <string>

class AppException {
private:
    std::string message;

public:
    AppException(std::string message);
    std::string what() const;
};

#endif // APPEXCEPTION_H