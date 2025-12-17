#pragma once
#include "Iterator.h"
#include <vector>

template<typename T>
struct Node {
    T data;
    Node* next = nullptr;
    explicit Node(const T& d) : data(d) {}
};

template<typename T>
class OneWayQueue {
    Node<T>* front = nullptr;
    Node<T>* back = nullptr;
    int count = 0;
public:
    using iterator = Iterator<T>;

    OneWayQueue() = default;
    ~OneWayQueue() { clear(); }

    bool empty() const { return front == nullptr; }
    int size() const { return count; }

    iterator begin() { return iterator(this, front); }
    iterator end() { return iterator(this, nullptr); }

    void add(const T& value) {
        Node<T>* node = new Node<T>(value);
        if (!front) {
            front = back = node;
        } else {
            back->next = node;
            back = node;
        }
        ++count;
    }

    bool removeFirst(const T& value) {
        Node<T>* prev = nullptr;
        Node<T>* cur = front;
        while (cur) {
            if (cur->data == value) {
                if (prev) prev->next = cur->next; else front = cur->next;
                if (cur == back) back = prev;
                delete cur;
                --count;
                return true;
            }
            prev = cur;
            cur = cur->next;
        }
        return false;
    }

    void clear() {
        Node<T>* cur = front;
        while (cur) {
            Node<T>* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        front = back = nullptr;
        count = 0;
    }

    template<typename Pred>
    std::vector<T> findAll(Pred pred) const {
        std::vector<T> res;
        Node<T>* cur = front;
        while (cur) {
            if (pred(cur->data)) res.push_back(cur->data);
            cur = cur->next;
        }
        return res;
    }

    std::vector<T> toVector() const {
        std::vector<T> res;
        res.reserve(count);
        Node<T>* cur = front;
        while (cur) {
            res.push_back(cur->data);
            cur = cur->next;
        }
        return res;
    }
};
