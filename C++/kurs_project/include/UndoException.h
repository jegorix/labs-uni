// UndoException.h
#ifndef UNDOEXCEPTION_H
#define UNDOEXCEPTION_H

#include "AppException.h"

class UndoException : public AppException {
public:
    UndoException(std::string message) : AppException(message) {}
};

#endif // UNDOEXCEPTION_H