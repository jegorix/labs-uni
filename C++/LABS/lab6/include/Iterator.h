#pragma once

template<typename T> struct Node;
template<typename T> class OneWayQueue;

template<typename T>
class Iterator {
    OneWayQueue<T>* owner;
    Node<T>* current;
public:
    Iterator(OneWayQueue<T>* o = nullptr, Node<T>* c = nullptr) : owner(o), current(c) {}

    T& operator*() { return current->data; }
    T* operator->() { return &current->data; }

    bool operator==(const Iterator& other) const { return current == other.current; }
    bool operator!=(const Iterator& other) const { return !(*this == other); }

    Iterator& operator++() {
        if (current) current = current->next;
        return *this;
    }
    Iterator operator++(int) { Iterator tmp(*this); ++(*this); return tmp; }

    // Для однонаправленного списка обратный шаг реализуем медленно
    Iterator& operator--() {
        if (!owner || !current) return *this;
        Node<T>* prev = nullptr;
        for (auto it = owner->begin(); it != owner->end(); ++it) {
            if (it.node() == current) break;
            prev = it.node();
        }
        current = prev;
        return *this;
    }
    Iterator operator--(int) { Iterator tmp(*this); --(*this); return tmp; }

    Node<T>* node() const { return current; }
};
