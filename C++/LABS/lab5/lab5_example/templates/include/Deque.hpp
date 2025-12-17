#pragma once

template<typename T>
struct DequeNode {
    T value;
    DequeNode* prev;
    DequeNode* next;
};

template<typename T>
class Deque {
private:
    DequeNode<T>* top;
    DequeNode<T>* bottom;

public:
    Deque();
    
    Deque(const Deque& other);
    
    Deque& operator=(const Deque& other);
    
    ~Deque();
    
    void pushFront(const T& value);
    
    void pushBack(const T& value);
    
    void popFront();
    
    void popBack();
    
    T& peekFirst();
        
    T& peekLast();
    
    bool isEmpty() const;
    
    int size() const;
    
    Deque<T> find(const T& value) const;
    
    void sort();
};

#include "Deque.tpp"
