#include "../include/File.h"
#include "../include/Shkolnik.h"
#include <exception>

BaseFile::BaseFile(const std::string& name) : filename(name) {}

//  Текстовый файл 
template<typename T>
void TextFile<T>::write(const std::vector<T>& items) {
    ofs.open(filename, std::ios::out | std::ios::trunc);
    if (!ofs.is_open()) {
        throw FileException(50, "Не удалось открыть текстовый файл для записи: " + filename);
    }
    for (const auto& item : items) {
        ofs << item.toTextRecord() << "\n";
    }
    ofs.close();
}

template<typename T>
std::vector<T> TextFile<T>::read() {
    ifs.open(filename);
    if (!ifs.is_open()) {
        throw FileException(51, "Не удалось открыть текстовый файл для чтения: " + filename);
    }
    std::vector<T> result;
    std::string line;
    while (std::getline(ifs, line)) {
        if (line.empty()) continue;
        try {
            result.push_back(T::fromTextRecord(line));
        } catch (const std::exception&) {
            // Пропускаем некорректные строки
        }
    }
    ifs.close();
    return result;
}

//  Бинарный файл 
template<typename T>
void BinaryFile<T>::write(const std::vector<T>& items) {
    bfs.open(filename, std::ios::binary | std::ios::out | std::ios::trunc);
    if (!bfs.is_open()) {
        throw FileException(52, "Не удалось открыть бинарный файл для записи: " + filename);
    }
    for (const auto& item : items) {
        auto rec = item.toBinaryRecord();
        bfs.write(reinterpret_cast<const char*>(&rec), sizeof(rec));
    }
    bfs.close();
}

template<typename T>
std::vector<T> BinaryFile<T>::read() {
    bfs.open(filename, std::ios::binary | std::ios::in);
    if (!bfs.is_open()) {
        throw FileException(53, "Не удалось открыть бинарный файл для чтения: " + filename);
    }
    std::vector<T> result;
    typename T::BinaryRecord rec{};
    while (bfs.read(reinterpret_cast<char*>(&rec), sizeof(rec))) {
        try {
            result.push_back(T::fromBinaryRecord(rec));
        } catch (const std::exception&) {
            // пропускаем некорректные записи
        }
    }
    bfs.close();
    return result;
}

// Явные инстанцирования для используемых типов
template class TextFile<Shkolnik>;
template class BinaryFile<Shkolnik>;
