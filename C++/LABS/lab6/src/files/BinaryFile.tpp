#include "../../include/Exceptions.h"

template <typename T>
void BinaryFile<T>::clearFile() const {
    std::ofstream file(filename, std::ios::out | std::ios::binary | std::ios::trunc);
    if (!file.is_open()) {
        throw FileException(62, "Не удалось очистить бинарный файл: " + filename);
    }
}

template <typename T>
void BinaryFile<T>::openFile(std::fstream& file, std::ios_base::openmode mode) const {
    file.open(filename, mode | std::ios::binary);
    if (!file.is_open()) {
        throw FileException(63, "Не удалось открыть бинарный файл: " + filename);
    }
}

template <typename T>
void BinaryFile<T>::saveRecord(const T& obj) {
    std::fstream file;
    openFile(file, std::ios::out | std::ios::app);
    const_cast<T&>(obj).saveBinaryRecord(file);
    file.close();
}

template <typename T>
std::vector<T> BinaryFile<T>::readAllRecords() {
    std::vector<T> items;
    std::fstream file;
    openFile(file, std::ios::in);
    while (true) {
        T* obj = T::readBinaryRecord(file);
        if (obj == nullptr) break;
        items.push_back(*obj);
        delete obj;
    }
    file.close();
    return items;
}
