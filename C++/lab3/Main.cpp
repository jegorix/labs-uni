#include "Airplane.h"
#include "Auto.h"
#include "Train.h"

int main()
{
    int choice = 0, new_speed = 0, new_stake = 0, new_max_altitude = 0, distance = 0;
    char* new_name = NULL, *city = NULL;
    Airplane planes[5];

    std::cout << " Введите первый объект класса:" << std::endl;
    std::cin >> planes[0];
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\033[2J\033[1;1H";

    for (int i = 1; i < 5; i++)
    {
        planes[i] = planes[0];
    }

    while (1)
    {
        planes[0].showMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\033[2J\033[1;1H";

        switch (choice)
        {
            case 0:
                return 0;
                break;

            case 1:
                std::cout << "	Вся информация об объекте" << std::endl;
                std::cout << planes[1];
                break;

            case 2:
                city = new char[32];
                std::cout << " Введите название города(только 32 символа): ";
                std::cin.getline(city, 32);
                std::cout << " Введите расстояние до города(км): ";
                std::cin >> distance;
                std::cout << "\033[2J\033[1;1H";
                std::cout << city << std::endl;
                /*	for (int i = 0; i < 5; i++)
                    {
                        std::cout << " Время перевозки: " << (planes[i].calculateTime(distance)) << "ч" << std::endl;
                        std::cout << " Стоимость перевозки: " << (planes[i].calculatePrice(distance)) << " руб" << std::endl;;
                    }*/

                std::cout << "\n Перевозка: " << city << "\n";

                // Верхняя граница
                std::cout << std::setfill('=') << std::setw(76) << "=" << "\n";
                std::cout << std::setfill(' ');

                // Заголовок
                std::cout << "| " << std::left << std::setw(5 - 1) << "№";
                std::cout << "| " << std::left << std::setw(20 - 1) << "Название";
                std::cout << "| " << std::right << std::setw(15) << "Время (ч)";
                std::cout << " | " << std::right << std::setw(20) << "Стоимость (руб)";
                std::cout << " |\n";

                // Разделительная линия
                std::cout << std::setfill('-') << std::setw(76) << "-" << "\n";
                std::cout << std::setfill(' ');

                // Данные строк — каждая строка разбита на отдельные cout
                for (int i = 0; i < 5; ++i) {
                    std::cout << "| " << std::left << std::setw(5 - 1) << i + 1;
                    std::cout << "| " << std::left << std::setw(20 - 1) << planes[i].getName();
                    std::cout << "| " << std::right << std::setw(15) << std::fixed << std::setprecision(2)
                              << planes[i].calculateTime(distance);
                    std::cout << " | " << std::right << std::setw(20) << std::fixed << std::setprecision(2)
                              << planes[i].calculatePrice(distance);
                    std::cout << " |\n";
                }

                // Нижняя граница
                std::cout << std::setfill('=') << std::setw(76) << "=" << "\n";
                std::cout << std::setfill(' ');
                delete[] city;
                break;

            case 3:
                std::cout << " Название: " << ((planes[1].getName()) ? planes[1].getName() : "неопределенно") << std::endl;
                break;

            case 4:
                new_name = new char[32];
                std::cout << " Введите новое название самолета(только 32 символа): ";
                std::cin.getline(new_name, 32);
                planes[1].setName(new_name);
                delete[] new_name;
                std::cout << "\033[2J\033[1;1H";
                break;

            case 5:
                std::cout << " Скорость: " << planes[1].getSpeed() << " км/ч" << std::endl;
                break;

            case 6:
                std::cout << " Введите новую скорость " << "\"" << ((planes[1].getName()) ? planes[1].getName() : "неопределенно") << "\"" << "(км/ч): ";
                std::cin >> new_speed;
                planes[1].setSpeed(new_speed);
                std::cout << "\033[2J\033[1;1H";
                break;

            case 7:
                std::cout << " Ставка: " << planes[1].getStake() << " руб/км" << std::endl;
                break;


            case 8:
                std::cout << " Введите новую ставку " << "\"" << ((planes[1].getName()) ? planes[1].getName() : "неопределенно") << "\"" << "(руб/ч): ";
                std::cin >> new_stake;
                planes[1].setStake(new_stake);
                std::cout << "\033[2J\033[1;1H";
                break;

            case 9:
                std::cout << " Макс. высота: " << planes[1].getMaxAltitude() << " км" << std::endl;
                break;

            case 10:
                std::cout << " Введите новую макс. высоту полета " << "\"" << ((planes[1].getName()) ? planes[1].getName() : "неопределенно") << "\"" << "(км): ";
                std::cin >> new_max_altitude;
                planes[1].setMaxAltitude(new_max_altitude);
                std::cout << "\033[2J\033[1;1H";
                break;
        }
    }
}