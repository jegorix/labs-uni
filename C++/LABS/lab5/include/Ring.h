#ifndef RING_H
#define RING_H

#include "RingNote.h"
#include <vector>
#include <functional>

// Обобщённый двусвязный кольцевой список.
// Реализация методов вынесена в Ring.cpp и инстанцируется для нужных типов.
template<typename T>
class Ring {
private:
    RingNote<T>* head;  // Указатель на произвольный стартовый узел
    int size;           // Количество элементов

public:
    Ring();                             // Конструктор: пустое кольцо
    ~Ring();                            // Деструктор: очистка всех узлов

    void add(const T& data);            // Добавить элемент (вставка перед head)
    bool remove(const T& data);         // Удалить первое совпадение по operator==
    void display() const;               // Вывести кольцо (ожидает printHeader/printTable у T)
    RingNote<T>* search(const T& data) const; // Найти элемент по точному совпадению
    std::vector<T> findAll(const std::function<bool(const T&)>& pred) const; // Все по предикату
    RingNote<T>* findFirst(const std::function<bool(const T&)>& pred) const; // Первый по предикату
    void sort();                        // Пузырьковая сортировка по getName()
    void sortWith(const std::function<bool(const T&, const T&)>& comp); // Сортировка с компаратором
    int getSize() const;                // Размер кольца
    bool isEmpty() const;               // Пусто ли
    void clear();                       // Очистить все узлы
};

#endif // RING_H
