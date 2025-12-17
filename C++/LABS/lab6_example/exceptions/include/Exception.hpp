#pragma once
#include <string>
#include <exception>

class Exception : public std::exception {
protected:
    int code;
    std::string message;
public:
    Exception(int errorCode, const std::string& errorMessage);
    virtual ~Exception() = default;
    
    int getCode() const;
    const char* what() const noexcept override;
};



