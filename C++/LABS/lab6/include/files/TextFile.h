#pragma once

#include "File.h"
#include "../Exceptions.h"
#include <vector>

// Текстовый файл для записи/чтения объектов, поддерживающих saveTextRecord/readTextRecord.
template <typename T>
class TextFile : public File {
public:
    explicit TextFile(const std::string& fname) : File(fname) {}
    ~TextFile() = default;

    void clearFile() const;
    void saveRecord(const T& obj);
    std::vector<T> readAllRecords();

private:
    void openFile(std::fstream& file, std::ios_base::openmode mode) const;
};

#include "../../src/files/TextFile.tpp"
