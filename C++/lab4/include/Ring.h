#ifndef RING_H
#define RING_H

#include "RingNote.h"
#include <iostream>
#include <cstring>
#include <iomanip>

// Шаблон класса Ring (кольцо)
template<typename T>
class Ring {
private:
    RingNote<T>* head;  // Указатель на начальный узел
    int size;           // Размер кольца

public:
    // Конструктор
    Ring() : head(nullptr), size(0) {}

    // Деструктор
    ~Ring() {
        clear();
    }

// Добавить элемент в кольцо
    void add(const T& data) {
        // Создаём новый узел (RingNote) с переданными данными
        RingNote<T>* newNode = new RingNote<T>(data);

        // Если кольцо пустое (первый элемент)
        if (head == nullptr) {
            head = newNode; // Устанавливаем голову на новый узел
            head->next = head;  // Так как это единственный элемент, его "следующий" — он сам
            head->prev = head;  // И его предыдущий — тоже он сам
        } else {
            // Иначе — кольцо уже существует, добавляем элемент в конец (перед head)

            // Указатель на последний элемент (тот, что перед head)
            RingNote<T>* last = head->prev;

            // Новый элемент должен указывать вперёд на head (чтобы замкнуть кольцо)
            newNode->next = head;

            // И назад — на бывший последний элемент
            newNode->prev = last;

            // У бывшего последнего элемента next теперь указывает на новый узел
            last->next = newNode;

            // А у head prev теперь должен указывать на новый последний элемент
            head->prev = newNode;
        }

        // Увеличиваем счётчик элементов в кольце
        size++;
    }

    // Удалить элемент из кольца
    bool remove(const T& data) {
        if (head == nullptr) {
            return false;
        }

        RingNote<T>* current = head;
        do {
            if (current->data == data) {
                // Найден элемент для удаления
                if (size == 1) {
                    // Единственный элемент
                    delete head;
                    head = nullptr;
                } else {
                    // Удаляем элемент из кольца
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

    // Вывести содержимое кольца на экран в виде таблицы
    void display() const {
        if (head == nullptr) {
            std::cout << "Кольцо пусто" << std::endl;
            return;
        }

        // Выводим заголовок таблицы один раз
        head->data.printHeader();
        
        // Выводим разделитель
        std::cout << " " << std::setfill('=') << std::setw(60) << "=" << std::setfill(' ') << std::endl;
        
        // Выводим данные каждого элемента в виде строки таблицы
        RingNote<T>* current = head;
        int count = 0;
        do {
            current->data.printTable();
            current = current->next;
            count++;
        } while (current != head && count < size);
        
        // Выводим нижний разделитель
        std::cout << " " << std::setfill('=') << std::setw(60) << "=" << std::setfill(' ') << std::endl;
    }

    // Поиск элемента в кольце
    RingNote<T>* search(const T& data) const {
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

    // Сортировка кольца (пузырьковая сортировка по имени)
    void sort() {
        if (head == nullptr || size <= 1) {
            return;
        }

        bool swapped;
        int iterations = 0;
        
        do {
            swapped = false;
            RingNote<T>* current = head;
            
            for (int i = 0; i < size - 1; i++) {
                RingNote<T>* next = current->next;
                
                // Сравниваем по имени (используя strcmp для char*)
                // Для классов с getName() методом
                char* name1 = current->data.getName();
                char* name2 = next->data.getName();
                
                if (name1 != nullptr && name2 != nullptr) {
                    if (strcmp(name1, name2) > 0) {
                        // Меняем местами данные
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

    // Получить размер кольца
    int getSize() const {
        return size;
    }

    // Проверка на пустоту
    bool isEmpty() const {
        return size == 0;
    }

    // Очистить кольцо
    void clear() {
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
};

#endif // RING_H

