#pragma once

#include "File.h"
#include "../Exceptions.h"
#include <vector>

// Бинарный файл для записи/чтения объектов, поддерживающих saveBinaryRecord/readBinaryRecord.
template <typename T>
class BinaryFile : public File {
public:
    explicit BinaryFile(const std::string& fname) : File(fname) {}
    ~BinaryFile() = default;

    void clearFile() const;
    void saveRecord(const T& obj);
    std::vector<T> readAllRecords();

private:
    void openFile(std::fstream& file, std::ios_base::openmode mode) const;
};

#include "../../src/files/BinaryFile.tpp"
