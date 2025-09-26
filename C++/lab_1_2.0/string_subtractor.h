#ifndef STRING_SUBTRACTOR_H                 // Защита от двойного включения
#define STRING_SUBTRACTOR_H

#include <string>                           // Для std::string

class string_subtractor
{
    int size;                               // Количество введённых строк
    std::string* ptr;                        // Динамический массив строк
public:
    string_subtractor(int init_size = 0);    // // Конструктор с параметром и по умолчанию
    string_subtractor(const string_subtractor&); // Конструктор копирования
    ~string_subtractor();                    // Деструктор

    void set_size(int new_size);             // Изменение размера массива строк
    void enter();                            // Ввод всех строк
    void print();                             // Вывод всех строк
    int subtract_lengths();                   // Последовательное вычитание длин
};

#endif // STRING_SUBTRACTOR_H