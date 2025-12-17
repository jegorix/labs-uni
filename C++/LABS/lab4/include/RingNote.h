#ifndef RINGNOTE_H
#define RINGNOTE_H

// Шаблон класса RingNote для представления узла кольца
template<typename T>
class RingNote {
public:
    T data;              // Данные, хранимые в узле
    RingNote<T>* next;   // Следующий узел (по кольцу)
    RingNote<T>* prev;   // Предыдущий узел (по кольцу)

    // Конструктор по умолчанию
    RingNote() : next(nullptr), prev(nullptr) {}

    // Конструктор с данными
    RingNote(const T& data) : data(data), next(nullptr), prev(nullptr) {}

    // Деструктор
    ~RingNote() {
        next = nullptr;
        prev = nullptr;
    }
};

#endif // RINGNOTE_H
