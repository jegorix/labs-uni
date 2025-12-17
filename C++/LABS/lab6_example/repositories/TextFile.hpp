#pragma once

#include "File.hpp"
#include <fstream>
#include <vector>
#include <string>

using namespace std;

template <typename T>
class TextFile : public File
{
public:
    TextFile(const string& fname) : File(fname) {}
    ~TextFile() = default;

    void saveRecord(const T& object);
    T* readRecord();
    vector<T*> readAllRecords();
    void clearFile() const;
    void openFile(fstream& file, ios_base::openmode mode) const;
};

#include "TextFile.tpp"
