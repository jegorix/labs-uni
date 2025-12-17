#ifndef CONTAINER_EXCEPTION_H
#define CONTAINER_EXCEPTION_H

#include "Exception.h"

// Ошибки, связанные с контейнерами (пустой контейнер, выход за границы и т.д.).
class ContainerException : public Exception {
public:
    ContainerException(int errorCode, const std::string& errorMessage) noexcept;
    ~ContainerException() override = default;
};

#endif // CONTAINER_EXCEPTION_H
