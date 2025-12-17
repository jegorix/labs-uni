// Реализация кольца для объектов Shkolnik
#include "../include/Ring.h"
#include <iostream>
#include <iomanip>
#include <cstring>

Ring::Ring() : head(nullptr), size(0) {}

Ring::~Ring() {
    clear();
}

void Ring::add(const Shkolnik& data) {
    auto* newNode = new RingNote<Shkolnik>(data);
    if (head == nullptr) {
        head = newNode;
        head->next = head;
        head->prev = head;
    } else {
        RingNote<Shkolnik>* last = head->prev;
        newNode->next = head;
        newNode->prev = last;
        last->next = newNode;
        head->prev = newNode;
    }
    size++;
}

bool Ring::remove(const Shkolnik& data) {
    if (head == nullptr) return false;

    RingNote<Shkolnik>* current = head;
    do {
        if (current->data == data) {
            if (size == 1) {
                delete head;
                head = nullptr;
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                if (current == head) head = head->next;
                delete current;
            }
            size--;
            return true;
        }
        current = current->next;
    } while (current != head);
    return false;
}

void Ring::display() const {
    if (head == nullptr) {
        std::cout << "Кольцо пусто" << std::endl;
        return;
    }

    head->data.printHeader();
    std::cout << " " << std::setfill('=') << std::setw(60) << "=" << std::setfill(' ') << std::endl;
    RingNote<Shkolnik>* current = head;
    int count = 0;
    do {
        current->data.printTable();
        current = current->next;
        count++;
    } while (current != head && count < size);
    std::cout << " " << std::setfill('=') << std::setw(60) << "=" << std::setfill(' ') << std::endl;
}

RingNote<Shkolnik>* Ring::search(const Shkolnik& data) const {
    if (head == nullptr) return nullptr;
    RingNote<Shkolnik>* current = head;
    do {
        if (current->data == data) return current;
        current = current->next;
    } while (current != head);
    return nullptr;
}

std::vector<Shkolnik> Ring::findAll(const std::function<bool(const Shkolnik&)>& pred) const {
    std::vector<Shkolnik> result;
    if (head == nullptr) return result;
    RingNote<Shkolnik>* current = head;
    int visited = 0;
    do {
        if (pred(current->data)) result.push_back(current->data);
        current = current->next;
        visited++;
    } while (current != head && visited < size);
    return result;
}

RingNote<Shkolnik>* Ring::findFirst(const std::function<bool(const Shkolnik&)>& pred) const {
    if (head == nullptr) return nullptr;
    RingNote<Shkolnik>* current = head;
    int visited = 0;
    do {
        if (pred(current->data)) return current;
        current = current->next;
        visited++;
    } while (current != head && visited < size);
    return nullptr;
}

void Ring::sort() {
    sortWith([](const Shkolnik& a, const Shkolnik& b){
        return std::strcmp(a.getName(), b.getName()) > 0;
    });
}

void Ring::sortWith(const std::function<bool(const Shkolnik&, const Shkolnik&)>& comp) {
    if (head == nullptr || size <= 1) return;
    bool swapped;
    int iterations = 0;
    do {
        swapped = false;
        RingNote<Shkolnik>* current = head;
        for (int i = 0; i < size - 1; ++i) {
            RingNote<Shkolnik>* next = current->next;
            if (comp(next->data, current->data)) {
                Shkolnik tmp = current->data;
                current->data = next->data;
                next->data = tmp;
                swapped = true;
            }
            current = next;
        }
        iterations++;
    } while (swapped && iterations < size);
}

int Ring::getSize() const { return size; }
bool Ring::isEmpty() const { return size == 0; }

void Ring::clear() {
    if (head == nullptr) return;
    RingNote<Shkolnik>* current = head->next;
    while (current != head) {
        RingNote<Shkolnik>* temp = current;
        current = current->next;
        delete temp;
    }
    delete head;
    head = nullptr;
    size = 0;
}

void Ring::forEach(const std::function<void(const Shkolnik&)>& fn) const {
    if (head == nullptr || size == 0) return;
    RingNote<Shkolnik>* current = head;
    int visited = 0;
    do {
        fn(current->data);
        current = current->next;
        visited++;
    } while (current != head && visited < size);
}

std::vector<Shkolnik> Ring::toVector() const {
    std::vector<Shkolnik> result;
    result.reserve(size);
    forEach([&](const Shkolnik& s){ result.push_back(s); });
    return result;
}
