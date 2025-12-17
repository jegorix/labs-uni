#include "../include/Ring.h"
#include "../include/Shkolnik.h"
#include "../include/Student.h"
#include <iostream>
#include <iomanip>
#include <cstring>

// Реализация шаблонных методов вынесена сюда и инстанцируется для Shkolnik.
// При необходимости других типов нужно добавить явную инстанциацию ниже.

// ----------------------------------------
// КОНСТРУКТОР / ДЕСТРУКТОР
// ----------------------------------------

template<typename T>
Ring<T>::Ring() : head(nullptr), size(0) {}

template<typename T>
Ring<T>::~Ring() {
    clear();
}

// ----------------------------------------
// БАЗОВЫЕ ОПЕРАЦИИ
// ----------------------------------------

template<typename T>
void Ring<T>::add(const T& data) {
    // Вставка нового узла перед head, хвост обновляется через head->prev
    RingNote<T>* newNode = new RingNote<T>(data);
    if (head == nullptr) {
        head = newNode;
        head->next = head;
        head->prev = head;
    } else {
        RingNote<T>* last = head->prev;
        newNode->next = head;
        newNode->prev = last;
        last->next = newNode;
        head->prev = newNode;
    }
    size++;
}

template<typename T>
bool Ring<T>::remove(const T& data) {
    if (head == nullptr) {
        return false;
    }
    RingNote<T>* current = head;
    do {
        if (current->data == data) {
            if (size == 1) {
                delete head;
                head = nullptr;
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                if (current == head) {
                    head = head->next;
                }
                delete current;
            }
            size--;
            return true;
        }
        current = current->next;
    } while (current != head);
    return false;
}

template<typename T>
void Ring<T>::display() const {
    if (head == nullptr) {
        std::cout << "Кольцо пусто" << std::endl;
        return;
    }
    // Предполагаем, что T умеет печатать заголовок и строку таблицы
    head->data.printHeader();
    std::cout << std::string(Uchaschiysya::TABLE_WIDTH, '=') << std::endl;

    RingNote<T>* current = head;
    int count = 0;
    do {
        current->data.printTable();
        current = current->next;
        count++;
    } while (current != head && count < size);

    std::cout << std::string(Uchaschiysya::TABLE_WIDTH, '=') << std::endl;
}

// ----------------------------------------
// ПОИСК
// ----------------------------------------

template<typename T>
RingNote<T>* Ring<T>::search(const T& data) const {
    if (head == nullptr) {
        return nullptr;
    }
    RingNote<T>* current = head;
    do {
        if (current->data == data) {
            return current;
        }
        current = current->next;
    } while (current != head);
    return nullptr;
}

template<typename T>
std::vector<T> Ring<T>::findAll(const std::function<bool(const T&)>& pred) const {
    std::vector<T> result;
    if (head == nullptr) {
        return result;
    }
    RingNote<T>* current = head;
    int visited = 0;
    do {
        if (pred(current->data)) {
            result.push_back(current->data);
        }
        current = current->next;
        visited++;
    } while (current != head && visited < size);
    return result;
}

template<typename T>
RingNote<T>* Ring<T>::findFirst(const std::function<bool(const T&)>& pred) const {
    if (head == nullptr) {
        return nullptr;
    }
    RingNote<T>* current = head;
    int visited = 0;
    do {
        if (pred(current->data)) {
            return current;
        }
        current = current->next;
        visited++;
    } while (current != head && visited < size);
    return nullptr;
}

// ----------------------------------------
// СОРТИРОВКИ
// ----------------------------------------

template<typename T>
void Ring<T>::sort() {
    if (head == nullptr || size <= 1) {
        return;
    }
    bool swapped;
    int iterations = 0;
    do {
        swapped = false;
        RingNote<T>* current = head;
        for (int i = 0; i < size - 1; ++i) {
            RingNote<T>* next = current->next;
            const char* name1 = current->data.getName();
            const char* name2 = next->data.getName();
            if (name1 != nullptr && name2 != nullptr) {
                if (std::strcmp(name1, name2) > 0) {
                    T temp = current->data;
                    current->data = next->data;
                    next->data = temp;
                    swapped = true;
                }
            }
            current = next;
        }
        iterations++;
    } while (swapped && iterations < size);
}

template<typename T>
void Ring<T>::sortWith(const std::function<bool(const T&, const T&)>& comp) {
    if (head == nullptr || size <= 1) {
        return;
    }
    bool swapped;
    int iterations = 0;
    do {
        swapped = false;
        RingNote<T>* current = head;
        for (int i = 0; i < size - 1; ++i) {
            RingNote<T>* next = current->next;
            if (comp(next->data, current->data)) {
                T temp = current->data;
                current->data = next->data;
                next->data = temp;
                swapped = true;
            }
            current = next;
        }
        iterations++;
    } while (swapped && iterations < size);
}

// ----------------------------------------
// СЛУЖЕБНЫЕ МЕТОДЫ
// ----------------------------------------

template<typename T>
int Ring<T>::getSize() const {
    return size;
}

template<typename T>
bool Ring<T>::isEmpty() const {
    return size == 0;
}

template<typename T>
void Ring<T>::clear() {
    if (head == nullptr) {
        return;
    }
    RingNote<T>* current = head->next;
    while (current != head) {
        RingNote<T>* temp = current;
        current = current->next;
        delete temp;
    }
    delete head;
    head = nullptr;
    size = 0;
}

// Явные инстанциации для используемых типов
template class Ring<Shkolnik>;
template class Ring<Student>;
