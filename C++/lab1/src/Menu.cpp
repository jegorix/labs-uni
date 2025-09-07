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
      cout << "\n╭────────────────────────────────────────╮\n"
                "│          Введите пункт меню:           │\n"
                "╰────────────────────────────────────────╯\n"
                "╰─> ";
        fflush(stdout);
        choice = fgetch();
        cout << choice << endl;
        py::print();

        switch (choice)
        {
            case '1':
              cout << "\n╭────────────────────────────────────────╮\n"
                        "│        Введите первую строку:          │\n"
                        "╰────────────────────────────────────────╯\n"
                        "╰─> ";
                cin.getline(input, buffer);
                arr.setFirstString(input);
              cout << "\n╭──────────────────────────────╮\n"
                        "│   Первая строка установлена  │\n"
                        "╰──────────────────────────────╯\n";
                break;

            case '2':
              cout << "\n╭────────────────────────────────────────╮\n"
                        "│        Введите вторую строку:          │\n"
                        "╰────────────────────────────────────────╯\n"
                        "╰─> ";
                cin.getline(input, buffer);
                arr.setSecondString(input);
              cout << "\n╭──────────────────────────────╮\n"
                        "│   Вторая строка установлена  │\n"
                        "╰──────────────────────────────╯\n";
                break;

            case '3':
                arr.printStrings();
                break;

            case '4':
                cout << "\n╭──────────────────────────────╮\n"
                        "  Разность длин: " << arr.calculateStringSub() << " \n"
                        "╰──────────────────────────────╯\n";
                break;

            case '5':
                cout << "\n╭──────────────────────────────╮\n"
                        "  Общая длина: " << arr.calculateTotalLength() << " \n"
                         "╰──────────────────────────────╯\n";
                break;

            case '6':
                arr.swapStrings();
              cout << "\n╭──────────────────────────────╮\n"
                        "│  Строки поменялись местами   │\n"
                        "╰──────────────────────────────╯\n";
              arr.printStrings();
                break;

            case '7':
              cout << "\n╭──────────────────────────────╮\n"
                        " " << (arr.isEmpty() ? "Обе строки пустые" : "Есть непустые строки") << " \n"
                        "╰──────────────────────────────╯\n";
                break;

            case '8':
              cout << "\n╭──────────────────────────────╮\n"
                        " Количество объектов: " << StringArray::getObjectCount() << " \n"
                        "╰──────────────────────────────╯\n";
                break;

            case '9':
                arr.clearStrings();
              cout << "\n╭──────────────────────────────╮\n"
                        "│        Строки удалены        │\n"
                        "╰──────────────────────────────╯\n";
                break;

            case '0':
              cout << "\n╭──────────────────────────────╮\n"
                        "│            Выход             │\n"
                        "╰──────────────────────────────╯\n";
                loadingAnimation(3, 300);
                break;

            default:
              cout << "\n╭──────────────────────────────╮\n"
                        "│        Неверный ввод!        │\n"
                        "╰──────────────────────────────╯\n";
                break;
        }

        if (choice != '0')
        {
            py::print();
            py::print();
            cout << "\nНажмите Enter для продолжения...";
            cin.get();
        }

    } while (choice != '0');

    delete[] input;
}


                // IMPROVE OUTPUT
// IMPROVE OUTPUT                  // IMPROVE OUTPUT
                // IMPROVE OUTPUT