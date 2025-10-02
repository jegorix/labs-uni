#include <iostream>
#include "MyString.h"

int main() {
    // Конструкторы
    MyString ob1;                      // конструктор по умолчанию
    MyString ob2("hello");             // из const char*
    MyString ob3(std::string("world"));// из std::string
    MyString ob4(ob2);                 // конструктор копирования

    std::cout << "Конструкторы:\n";
    std::cout << "ob1: \"" << ob1 << "\"\n";
    std::cout << "ob2: \"" << ob2 << "\"\n";
    std::cout << "ob3: \"" << ob3 << "\"\n";
    std::cout << "ob4 (копия ob2): \"" << ob4 << "\"\n\n";

    // Оператор присваивания
    ob1 = ob3;
    std::cout << "После присваивания ob1 = ob3: " << ob1 << "\n\n";

    // Доступ к символам
    std::cout << "ob3[0]: " << ob3[0] << "\n";
    ob3[0] = 'W';
    std::cout << "После изменения ob3[0]='W': " << ob3 << "\n\n";

    // Подстрока
    MyString sub = ob3(1, 3);
    std::cout << "Подстрока ob3(1,3): " << sub << "\n\n";

    // Конкатенация
    MyString ob5 = ob2 + ob3;
    MyString ob6 = ob2 + std::string("!!!");
    MyString ob7 = std::string("***") + ob2;
    MyString ob8 = ob2 + "###";
    MyString ob9 = "+++" + ob2;

    std::cout << "Конкатенация:\n";
    std::cout << "ob2 + ob3: " << ob5 << "\n";
    std::cout << "ob2 + std::string(\"!!!\"): " << ob6 << "\n";
    std::cout << "std::string(\"***\") + ob2: " << ob7 << "\n";
    std::cout << "ob2 + \"###\": " << ob8 << "\n";
    std::cout << "\"+++\" + ob2: " << ob9 << "\n\n";


    // Тест конкатенации с константной строкой первой
    MyString ob = "ghh" + ob1 + ob2 + "ghh";

    std::cout << "Тест: ob = \"ghh\" + ob1 + ob2 + \"ghh\"\n";
    std::cout << "ob: " << ob << std::endl;


    // Оператор +=
    ob5 += ob6;
    std::cout << "После ob5 += ob6: " << ob5 << "\n\n";

    // Префиксный и постфиксный ++/--
    std::cout << "До ++ob2: " << ob2 << "\n";
    ++ob2; // префиксный ++
    std::cout << "После ++ob2: " << ob2 << "\n";

    std::cout << "До ob2++: " << ob2 << "\n";
    ob2++; // постфиксный ++
    std::cout << "После ob2++: " << ob2 << "\n";

    std::cout << "До --ob2: " << ob2 << "\n";
    --ob2; // префиксный --
    std::cout << "После --ob2: " << ob2 << "\n";

    std::cout << "До ob2--: " << ob2 << "\n";
    ob2--; // постфиксный --
    std::cout << "После ob2--: " << ob2 << "\n\n";

    // Сравнение по длине
    std::cout << "ob2 > ob3: " << (ob2 > ob3) << "\n";
    std::cout << "ob2 < ob3: " << (ob2 < ob3) << "\n\n";

    // Ввод/вывод
    MyString inputStr;
    std::cout << "Введите строку: ";
    std::cin >> inputStr;
    std::cout << "Вы ввели: " << inputStr << "\n";

    return 0;
}