#ifndef INPUT_EXCEPTION_H
#define INPUT_EXCEPTION_H

#include "Exception.h"

// Ошибки пользовательского ввода.
class InputException : public Exception {
public:
    InputException(int errorCode, const std::string& errorMessage) noexcept;
    ~InputException() override = default;
};

#endif // INPUT_EXCEPTION_H
