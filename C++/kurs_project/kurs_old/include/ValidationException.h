// ValidationException.h
#ifndef VALIDATIONEXCEPTION_H
#define VALIDATIONEXCEPTION_H

#include "AppException.h"

class ValidationException : public AppException {
public:
    ValidationException(std::string message) : AppException(message) {}
};

#endif // VALIDATIONEXCEPTION_H