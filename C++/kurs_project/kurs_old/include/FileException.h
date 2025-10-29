// FileException.h
#ifndef FILEEXCEPTION_H
#define FILEEXCEPTION_H

#include "AppException.h"

class FileException : public AppException {
public:
    FileException(std::string message) : AppException(message) {}
};

#endif // FILEEXCEPTION_H