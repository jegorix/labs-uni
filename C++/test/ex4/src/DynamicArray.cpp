#include "DynamicArray.h"

template <typename T>
DynamicArray<T>::DynamicArray(size_t initialCapacity)
{
    size = 0;
    if(initialCapacity > 0)
    {
        capacity = initialCapacity;
        data = new T[capacity];
    }
    else 
    {
        capacity = 1;
        data = new T[capacity];
    }
}

template <typename T>
DynamicArray<T>::~DynamicArray()
{
    delete[] data;
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other)
{
    capacity = other.capacity;
    size = other.size;
    data = new T[capacity];
    for(size_t i = 0; i < size; i++)
    {
        data[i] = other.data[i];
    }
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other)
{
    if(this != &other)
    {
        delete data[];
        capacity = other.capacity;
        size = other.size;
        data = new T[capacity];

        for(size_t i = 0; i < size; i++)
        {
            data[i] = other.data[i];
        }
    }
    return *this;
}

template <typename T>
void DynamicArray<T>::push_back(const T& value)
{
    if(size >= capacity)
    {
        capacity *= 2;
        T* newData = new T[capacity];
        for(size_t i = 0; i < size; i++)
        {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }
    data[size++] = value;
}


template <typename T>
void DynamicArray<T>::pop_back()
{
    if(size > 0)
    {
        size--;
    }
}

template <typename T>
T& DynamicArray<T>::at(size_t index)
{
    if(index >= size)
    {
        throw std::out_of_range("Index out of range");
    }

    return data[index];

}

template <typename T>
const T& DynamicArray<T>::at(size_t index) const
{
    if(index >= size)
    {
        throw std::out_of_range("Index out of range");
    }

    return data[index];
}

template <typename T>
size_t DynamicArray<T>::getSize() const
{
    return size;
}

template <typename T>
bool DynamicArray<T>::isEmpty() const 
{
    return size == 0;
}

template <typename T>
T& DynamicArray<T>::operator[](size_t index)
{
    return data[index];
}

template <typename T>
const T& DynamicArray<T>::operator[](size_t index) const
{
    return data[index];
}

template <typename T>
void DynamicArray<T>::print() const
{
    std::cout << "["
    for(size_t i = 0; i < size; i++)
    {
        std::cout << data[i];
        if(i < size - 1)
        {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

template <typename T>
int DynamicArray<T>::find(const T& value) const
{
    for(size_t i = 0; i < size; i++)
    {
        if(data[i] == value)
        {
            return static_cast<int>(i);
        }
    }

    return -1;
}

template <typename T>
void DynamicArray<T>::sort()
{
    for(size_t i = 0; i < size - 1; i++)
    {
        size_t minIndex = i;
        
        for(size_t j = i + 1; j < size; j++)
        {
            if(data[j] < data[minIndex])
            {
                minIndex = j;
            }
        }
        
        if(minIndex != i)
        {
            std::swap(data[i], data[minIndex]);
        }
    }
}


template <typename T>
void DynamicArray<T>::remove(size_t index)
{
    if(index >= size)
    {
        throw::std::out_of_range("Index out of range");
    }

    for(size_t i; i < size; i++)
    {
        data[i] = data[i + 1];
    }

    size--;
}

template <typename T>
void DynamicArray<T>::insert(size_t index, const T& value)
{
    if(index > size)
    {
        throw std::out_of_range("Index out of range");
    }

    if(size >= capacity)
    {
        reserve(capacity * 2);
    }

    for(size_t i = size; i > index; i--)
    {
        data[i] = data[i-1];
    }

    data[index] = value;
    size++;
}

template <typename T>
void DynamicArray<T>::reverse(size_t newCapacity)
{

    if(newCapacity <= capacity)
    {
        return;
    }

    T* newData = new T[newCapacity];
    for(size_t i = 0; i < size; i++)
    {
        newData[i] = data[i];
    }

    delete data[];
    data = newData;
    capacity = newCapacity;

}