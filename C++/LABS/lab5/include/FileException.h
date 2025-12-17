#ifndef FILE_EXCEPTION_H
#define FILE_EXCEPTION_H

#include "Exception.h"

// Ошибки при работе с файлами.
class FileException : public Exception {
public:
    FileException(int errorCode, const std::string& errorMessage) noexcept;
    ~FileException() override = default;
};

#endif // FILE_EXCEPTION_H
