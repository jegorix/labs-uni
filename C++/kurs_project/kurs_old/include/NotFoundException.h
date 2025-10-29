// NotFoundException.h
#ifndef NOTFOUNDEXCEPTION_H
#define NOTFOUNDEXCEPTION_H

#include "AppException.h"

class NotFoundException : public AppException {
public:
    NotFoundException(std::string message) : AppException(message) {}
};

#endif // NOTFOUNDEXCEPTION_H