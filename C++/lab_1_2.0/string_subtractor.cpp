#include "string_subtractor.h"
#include <iostream>
#include <limits>
#include <iomanip>

// Конструктор: выделяет память под init_size строк
string_subtractor::string_subtractor(int init_size)
{
    ptr = new std::string[init_size];        // Создание массива строк
    size = init_size;                        // Запоминаем размер
}

// Конструктор копирования: глубокое копирование массива строк
string_subtractor::string_subtractor(const string_subtractor& other)
{
    ptr = new std::string[other.size];       // Выделяем память под строки
    size = other.size;                        // Копируем размер
    for (int i = 0; i < size; i++)            // Копируем каждую строку
        ptr[i] = other.ptr[i];
}

// Деструктор: освобождает динамическую память
string_subtractor::~string_subtractor()
{
    delete[] ptr;                             // Удаляем массив строк
}

// Изменение размера массива с сохранением существующих строк
void string_subtractor::set_size(int new_size)
{
    std::string* new_ptr = new std::string[new_size]; // Новый массив
    for (int i = 0; i < size && i < new_size; i++)    // Копируем строки
        new_ptr[i] = ptr[i];
    delete[] ptr;                                     // Старый массив удаляем
    size = new_size;                                   // Новый размер
    ptr = new_ptr;                                     // Новый указатель
}

// Ввод всех строк с клавиатуры
void string_subtractor::enter()
{
    for (int i = 0; i < size; i++)                                      // Для каждой строки
    {
        std::cout << "Строка " << i + 1 << ": ";                        // Приглашение
        std::getline(std::cin, ptr[i]);                                 // Ввод всей строки
    }
}

// Вывод всех строк на экран
void string_subtractor::print()
{
    for (int i = 0; i < size; i++)                                      // Каждая строка
        std::cout << std::setw(3) << i + 1 << ") " << ptr[i] << '\n';    // Номер и текст
}


// Подсчёт количества символов в UTF-8 строке
int utf8_len(const std::string& s) {
    int count = 0;
    for (unsigned char c : s)
        if ((c & 0xC0) != 0x80) // не продолжение символа
            ++count;
    return count;
}

// Последовательное вычитание длин: длина первой минус длины остальных
int string_subtractor::subtract_lengths()
{
    if (size == 0) return 0;                  // Если строк нет — вернуть 0
    int result = utf8_len(ptr[0]);             // Начинаем с длины первой строки
    for (int i = 1; i < size; i++)            // Проходим остальные строки
        result -= utf8_len(ptr[i]);            // Вычитаем их длины
    return result;                            // Возвращаем результат
}

