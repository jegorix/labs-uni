#include "include/Uchaschiysya.h"
#include "include/Shkolnik.h"
#include "include/Student.h"

void showResult(Shkolnik shkolniki[]);

int main()
{
 // школьники
    int choice = 0, new_age = 0, new_grade = 0;
    char* new_name = NULL;
    Shkolnik shkolniki[5];

    std::cout << " Введите первый объект класса:" << std::endl;
    std::cin >> shkolniki[0];
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\033[2J\033[1;1H";

    for (int i = 1; i < 5; i++)
    {
        shkolniki[i] = shkolniki[0];
    }

    while (1)
    {
        shkolniki[0].showMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\033[2J\033[1;1H";

        switch (choice)
        {
            case 0:
                return 0;
                break;

            case 1:
                std::cout << " " << std::setfill('=') << std::setw(80) << "=" << std::setfill(' ') << std::endl;
                std::cout << " | " << std::left << std::setw(20 - 2) << "Имя";
                std::cout << "| " << std::left << std::setw(20 - 2) << "Возраст";
                std::cout << "| " << std::left << std::setw(19 - 2) << "Класс" << "|" << std::endl;
                std::cout << " " << std::setfill('=') << std::setw(80) << "=" << std::setfill(' ') << std::endl;
                for (int i = 0; i < 5; i++)
                {
                    std::cout << shkolniki[i];
                }
                std::cout << " " << std::setfill('=') << std::setw(80) << "=" << std::setfill(' ') << std::endl;
                break;

            case 2:
                showResult(shkolniki);
                break;

            case 3:
                std::cout << " Имя: " << ((shkolniki[1].getName()[0] != '\0') ? shkolniki[1].getName() : "неопределенно") << std::endl;
                break;

            case 4:
                new_name = new char[32];
                std::cout << " Введите новое имя (до 31 символа): ";
                std::cin.getline(new_name, 32);
                shkolniki[1].setName(new_name);
                delete[] new_name;
                std::cout << "\033[2J\033[1;1H";
                break;

            case 5:
                std::cout << " Возраст: " << shkolniki[1].getAge() << " лет" << std::endl;
                break;

            case 6:
                std::cout << " Введите новый возраст " << "\"" << ((shkolniki[1].getName()[0] != '\0') ? shkolniki[1].getName() : "неопределенно") << "\"" << " (лет): ";
                std::cin >> new_age;
                shkolniki[1].setAge(new_age);
                std::cout << "\033[2J\033[1;1H";
                break;

            case 7:
                std::cout << " Класс: " << shkolniki[1].getGrade() << std::endl;
                break;

            case 8:
                std::cout << " Введите новый класс " << "\"" << ((shkolniki[1].getName()[0] != '\0') ? shkolniki[1].getName() : "неопределенно") << "\"" << ": ";
                std::cin >> new_grade;
                shkolniki[1].setGrade(new_grade);
                std::cout << "\033[2J\033[1;1H";
                break;
        }
    }
}

void showResult(Shkolnik shkolniki[])
{
    std::cout << "\033[2J\033[1;1H";
    std::cout << " Список школьников:" << std::endl;

    std::cout << " " << std::setfill('=') << std::setw(61 - 1) << "=" << std::setfill(' ') << std::endl;

    std::cout << " |" << std::setw(3) << std::left << " №" << " |" << std::setw(21) << std::right << "Имя";
    std::cout << std::setw(6) << " |" << std::setw(17) << std::right << "Класс" << std::setw(10) << " |" << std::endl;

    std::cout << " " << std::setfill('=') << std::setw(61 - 1) << "=" << std::setfill(' ') << std::endl;

    for (int i = 0; i < 5; i++)
    {
        std::cout << " | " << std::left << std::setw(5 - 2) << i + 1;
        std::cout << "| " << std::left << std::setw(25 - 2) << ((shkolniki[i].getName()[0] != '\0') ? shkolniki[i].getName() : "неопределенно");
        std::cout << "| " << std::left << std::setw(23 - 2) << shkolniki[i].getGrade() << " |" << std::endl;
    }

    std::cout << " " << std::setfill('=') << std::setw(61 - 1) << "=" << std::setfill(' ') << std::endl;
}