#include "../include/Menu.h"
#include "../include/utils.h"
#include "../include/custom/fgetch.h"
#include "../include/custom/print.h"
#include <iostream>
using namespace std;

void Menu::showMainMenu()
{
    cout << "\n╔═════════════════════════════════════════════════════════╗\n"
            "║                                                         ║\n"
            "║                       ГЛАВНОЕ МЕНЮ                      ║\n"
            "║                                                         ║\n"
            "║   1. Установить первую строку                           ║\n"
            "║   2. Установить вторую строку                           ║\n"
            "║   3. Показать строки                                    ║\n"
            "║   4. Посчитать разность длин                            ║\n"
            "║   5. Общая длина строк                                  ║\n"
            "║   6. Поменять строки местами                            ║\n"
            "║   7. Проверить пустые ли строки                         ║\n"
            "║   8. Количество объектов                                ║\n"
            "║   9. Удалить строки                                     ║\n"
            "║   0. Выход                                              ║\n"
            "║                                                         ║\n"
            "╚═════════════════════════════════════════════════════════╝\n";
}

void Menu::run()
{
    StringArray arr;
    char choice;

    const int buffer = 256;
    char* input = new char[buffer];

    do
    {

        clearScreen();
        showMainMenu();
        cout << "\nВведите пункт меню: ";
        fflush(stdout);
        choice = fgetch();
        cout << choice << endl;
        py::print();

        switch (choice)
        {
            case '1':
                cout << "Введите первую строку: ";
                cin.getline(input, buffer);
                arr.setFirstString(input);
                break;

            case '2':
                cout << "Введите вторую строку: ";
                cin.getline(input, buffer);
                arr.setSecondString(input);
                break;

            case '3':
                arr.printStrings();
                break;

            case '4':
                cout << "Разность длин: " << arr.calculateStringSub() << endl;
                break;

            case '5':
                cout << "Общая длина: " << arr.calculateTotalLength() << endl;
                break;

            case '6':
                arr.swapStrings();
                cout << "Строки поменялись местами." << endl;
                break;

            case '7':
                cout << (arr.isEmpty() ? "Обе строки пустые" : "Есть непустые строки") << endl;
                break;

            case '8':
                cout << "Количество объектов: " << StringArray::getObjectCount() << endl;
                break;

            case '9':
                arr.clearStrings();
                cout << "Строки удалены." << endl;
                break;

            case '0':
                cout << "Выход";
                loadingAnimation(3, 300);
                break;

            default:
                cout << "Неверный ввод!" << endl;
                break;
        }

        if (choice != '0')
        {
            cout << "\nНажмите Enter для продолжения...";
            cin.get();
        }

    } while (choice != '0');

    delete[] input;
}