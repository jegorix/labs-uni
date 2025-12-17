#include "../exceptions/include/FileException.hpp"
#include <sstream>

template <typename T>
void TextFile<T>::clearFile() const
{
    ofstream file(filename, ios::out | ios::trunc);
    if (!file.is_open())
    {
        throw FileException(60, "Error clear file: " + filename);
    }
    file.close();
}

template <typename T>
void TextFile<T>::openFile(fstream& file, ios_base::openmode mode) const
{
    file.open(filename, mode);
    if (!file.is_open())
    {
        throw FileException(61, "Error open file: " + filename);
    }
}

template <typename T>
void TextFile<T>::saveRecord(const T& object)
{
    fstream file;
    openFile(file, ios::out | ios::app);
    const_cast<T&>(object).saveTextRecord(file);
    file << '\n';
    file.close();
}

template <typename T>
T* TextFile<T>::readRecord()
{
    fstream file;
    openFile(file, ios::in);
    T* object = T::readTextRecord(file);
    file.close();
    return object;
}

template <typename T>
vector<T*> TextFile<T>::readAllRecords()
{
    vector<T*> records;
    fstream file;
    openFile(file, ios::in);

    while (true)
    {
        T* object = T::readTextRecord(file);
        if (object == nullptr)
        {
            break;
        }
        records.push_back(object);
    }

    file.close();
    return records;
}
