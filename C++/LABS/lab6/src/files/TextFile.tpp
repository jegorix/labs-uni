#include "../../include/Exceptions.h"

template <typename T>
void TextFile<T>::clearFile() const {
    std::ofstream file(filename, std::ios::out | std::ios::trunc);
    if (!file.is_open()) {
        throw FileException(60, "Не удалось очистить файл: " + filename);
    }
}

template <typename T>
void TextFile<T>::openFile(std::fstream& file, std::ios_base::openmode mode) const {
    file.open(filename, mode);
    if (!file.is_open()) {
        throw FileException(61, "Не удалось открыть файл: " + filename);
    }
}

template <typename T>
void TextFile<T>::saveRecord(const T& obj) {
    std::fstream file;
    openFile(file, std::ios::out | std::ios::app);
    const_cast<T&>(obj).saveTextRecord(file);
    file << '\n';
    file.close();
}

template <typename T>
std::vector<T> TextFile<T>::readAllRecords() {
    std::vector<T> items;
    std::fstream file;
    openFile(file, std::ios::in);
    while (true) {
        T* obj = T::readTextRecord(file);
        if (obj == nullptr) break;
        items.push_back(*obj);
        delete obj;
    }
    file.close();
    return items;
}
