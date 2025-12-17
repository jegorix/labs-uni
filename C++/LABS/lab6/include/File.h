#ifndef LAB6_FILE_H
#define LAB6_FILE_H

#include <fstream>
#include <string>
#include <vector>
#include <exception>
#include "Exceptions.h"

// Базовый (не шаблонный) класс файла: хранит имя и потоки
class BaseFile {
protected:
    std::string filename;
    std::ifstream ifs;
    std::ofstream ofs;
    std::fstream bfs;

public:
    explicit BaseFile(const std::string& name);
    virtual ~BaseFile() = default;
};

// Шаблон текстового файла: пишет/читает записи типа T (предполагается наличие toTextRecord/fromTextRecord)
template<typename T>
class TextFile : public BaseFile {
public:
    using BaseFile::BaseFile;

    void write(const std::vector<T>& items);
    std::vector<T> read();
};

// Шаблон бинарного файла: пишет/читает записи типа T через T::BinaryRecord
template<typename T>
class BinaryFile : public BaseFile {
public:
    using BaseFile::BaseFile;

    void write(const std::vector<T>& items);
    std::vector<T> read();
};

#endif // LAB6_FILE_H
