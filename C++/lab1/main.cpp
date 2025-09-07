#include <iostream>
#include <cstdlib>
#include "include/custom/print.h"
#include "include/utils.h"
#include "include/Menu.h"

void printLabHeader() {
    clearScreen();
    std::cout <<  "\n╔═════════════════════════════════════════════════════════╗\n"
                    "║                                                         ║\n"
                    "║               Лабораторная работа №1                    ║\n"
                    "║                                                         ║\n"
                    "║               Тема: Классы и объекты                    ║\n"
                    "║                                                         ║\n"
                    "║  Задача: Реализовать класс, выполняющий вычитание строк ║\n"
                    "║                                                         ║\n"
                    "║   Код выполняет все требования:                         ║\n"
                    "║     - Деление программы на заголовочные файлы           ║\n"
                    "║     - Каждый класс в отдельном .h и .cpp файле          ║\n"
                    "║     - Отдельный .cpp файл для main                      ║\n"
                    "║                                                         ║\n"
                    "║   Автор: Новицкий Егор                                  ║\n"
                    "║                                                         ║\n"
                    "╚═════════════════════════════════════════════════════════╝\n";

}

int main() {
    printLabHeader();
    std::cout << "\nНажмите Enter для начала...";
    std::cin.get();
    std::cout << "\nЗагрузка";
    loadingAnimation(3, 300);
    Menu::run();
//    std::cin.get();

    return 0;
}