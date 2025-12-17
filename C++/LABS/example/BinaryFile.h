#pragma once
#include "File.h"
#include "FileException.h" 

template<typename T>
class BinaryFile : public File
{
public:
    explicit BinaryFile(const std::string& filename) : File(filename) {}

    void openForWrite();
    void openForRead();
    void write(const T& obj);
    T read();
    bool eof() const;
};

#include "BinaryFile.hpp"