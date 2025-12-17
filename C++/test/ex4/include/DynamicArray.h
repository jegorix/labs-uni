#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H
#include <iostream>

template <typename T>
class DynamicArray 
{
    private:
        T* data;
        size_t capacity;
        size_t size;

    public:
        DynamicArray(size_t initialCapacity = 10);
        ~DynamicArray();
        DynamicArray(const DynamicArray<T>& other);
        DynamicArray<T>& operator=(const DynamicArray<T>& other);

        void push_back(const T& value);
        void pop_back();
        T& at(size_t index);
        const T& at(size_t index) const;
        size_t getSize() const;
        bool isEmpty() const;

        T& operator[](size_t index);
        const T& operator[](size_t index) const;
        
        void print() const;

        int find(const T& value) const;
        void sort();
        void remove(size_t index);
        void insert(size_t index, const T& value);

        void reverse(size_t newCapacity);


};

#endif