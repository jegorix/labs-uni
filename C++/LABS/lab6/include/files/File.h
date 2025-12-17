#pragma once

#include <string>
#include <fstream>

// Базовый класс для работы с файлами (текст/бинарные).
class File {
protected:
    std::string filename;
    std::ifstream iFile;
    std::ofstream oFile;
    std::fstream fFile;

public:
    explicit File(const std::string& fname) : filename(fname) {}
    virtual ~File();
};
