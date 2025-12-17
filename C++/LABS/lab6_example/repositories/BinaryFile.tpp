#include "../exceptions/include/FileException.hpp"
#include <sstream>

template <typename T>
void BinaryFile<T>::clearFile() const
{
    ofstream file(filename, ios::out | ios::binary | ios::trunc);
    if (!file.is_open())
    {
        throw FileException(62, "Error clear binary file: " + filename);
    }
    file.close();
}

template <typename T>
void BinaryFile<T>::openFile(fstream& file, ios_base::openmode mode) const
{
    file.open(filename, mode | ios::binary);
    if (!file.is_open())
    {
        throw FileException(63, "Error open binary file: " + filename);
    }
}

template <typename T>
void BinaryFile<T>::saveRecord(const T& object)
{
    fstream file;
    openFile(file, ios::out | ios::app);
    const_cast<T&>(object).saveBinaryRecord(file);
    file.close();
}

template <typename T>
T* BinaryFile<T>::readRecord()
{
    fstream file;
    openFile(file, ios::in);
    T* object = T::readBinaryRecord(file);
    file.close();
    return object;
}

template <typename T>
vector<T*> BinaryFile<T>::readAllRecords()
{
    vector<T*> records;
    fstream file;
    openFile(file, ios::in);

    while (true)
    {
        T* object = T::readBinaryRecord(file);
        if (object == nullptr)
        {
            break;
        }
        records.push_back(object);
    }

    file.close();
    return records;
}
