#ifndef RINGNOTE_H
#define RINGNOTE_H

template<typename T>
class RingNote {
public:
    T data;
    RingNote<T>* next;
    RingNote<T>* prev;

    RingNote() : next(nullptr), prev(nullptr) {}
    RingNote(const T& data) : data(data), next(nullptr), prev(nullptr) {}

    ~RingNote() {
        next = nullptr;
        prev = nullptr;
    }
};

#endif // RINGNOTE_H
