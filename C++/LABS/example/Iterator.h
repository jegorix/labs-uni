#pragma once

template<typename T>
struct Unit;

template<typename T>
class OneWayQueue;

template<typename T>
class Iterator
{
private:
    OneWayQueue<T>* owner = nullptr;
    Unit<T>* current = nullptr;

public:
    Iterator() {};

    Iterator(OneWayQueue<T>* owner, Unit<T>* current)
    {
        this->owner = owner;
        this->current = current;
    }

    // разыменование
    T& operator*();
    T* operator->();

    // сравнение
    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;

    // prefix ++
    Iterator& operator++();

    // postfix ++
    Iterator operator++(int);
    

    // prefix -- (медленная реализация для однонаправленного списка)
    Iterator& operator--();

    // postfix --
    Iterator operator--(int);

    Unit<T>* getNode() const;
};

#include "Iterator.hpp"