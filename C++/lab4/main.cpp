#include "include/Uchaschiysya.h"
#include "include/Shkolnik.h"
#include "include/Student.h"
#include "include/Ring.h"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void printMenu() {
    const int width = 60;
    cout << "\n " << setfill('=') << setw(width) << "=" << setfill(' ') << endl;
    string title = "СИСТЕМА УПРАВЛЕНИЯ ШКОЛЬНИКАМИ С КОЛЬЦОМ";
    int padding = (width - 2 - (int)title.length()) / 2;
    cout << " |" << setw(padding) << " " << title << setw(width - 2 - padding - (int)title.length()) << " " << "|" << endl;
    cout << " " << setfill('=') << setw(width) << "=" << setfill(' ') << endl;
    cout << " |  1. Добавить школьника в кольцо" << setw(width - 34) << " " << "|" << endl;
    cout << " |  2. Показать всех из кольца" << setw(width - 28) << " " << "|" << endl;
    cout << " |  3. Удалить школьника из кольца" << setw(width - 31) << " " << "|" << endl;
    cout << " |  4. Найти школьника в кольце" << setw(width - 30) << " " << "|" << endl;
    cout << " |  5. Отсортировать кольцо" << setw(width - 26) << " " << "|" << endl;
    cout << " |  6. Показать размер кольца" << setw(width - 27) << " " << "|" << endl;
    cout << " |  0. Выход" << setw(width - 13) << " " << "|" << endl;
    cout << " " << setfill('=') << setw(width) << "=" << setfill(' ') << endl;
    cout << " Выберите опцию: ";
}

int main() {
    Ring<Shkolnik> ring;  // Кольцо для хранения школьников
    int choice;
    
    do {
        printMenu();
        cin >> choice;
        clearInput();
        
        switch (choice) {
            case 1: {
                // Добавить школьника
                Shkolnik newObject;
                cout << "Введите данные школьника:\n";
                cin >> newObject;
                ring.add(newObject);
                cout << "Школьник добавлен в кольцо успешно!\n";
                break;
            }
            case 2: {
                // Показать всех
                cout << "\n" << setfill('=') << setw(60) << "=" << setfill(' ') << endl;
                cout << "                 ШКОЛЬНИКИ В КОЛЬЦЕ" << endl;
                cout << setfill('=') << setw(60) << "=" << setfill(' ') << endl;
                if (!ring.isEmpty()) {
                    ring.display();
                } else {
                    cout << "Кольцо пусто." << endl;
                    cout << setfill('=') << setw(60) << "=" << setfill(' ') << endl;
                }
                break;
            }
            case 3: {
                // Удалить школьника
                if (ring.isEmpty()) {
                    cout << "Кольцо пусто. Нечего удалять.\n";
                    break;
                }
                
                Shkolnik searchObj;
                cout << "Введите данные школьника для удаления:\n";
                cout << "Введите имя (до 31 символа): ";
                char name[32];
                cin.getline(name, 32);
                searchObj.setName(name);
                cout << "Введите возраст: ";
                int age;
                cin >> age;
                searchObj.setAge(age);
                cout << "Введите класс: ";
                int grade;
                cin >> grade;
                searchObj.setGrade(grade);
                clearInput();
                
                if (ring.remove(searchObj)) {
                    cout << "Школьник удален из кольца успешно!\n";
                } else {
                    cout << "Школьник не найден в кольце.\n";
                }
                break;
            }
            case 4: {
                // Найти школьника
                if (ring.isEmpty()) {
                    cout << "Кольцо пусто. Нечего искать.\n";
                    break;
                }
                
                Shkolnik searchObj;
                cout << "Введите данные школьника для поиска:\n";
                cout << "Введите имя (до 31 символа): ";
                char name[32];
                cin.getline(name, 32);
                searchObj.setName(name);
                cout << "Введите возраст: ";
                int age;
                cin >> age;
                searchObj.setAge(age);
                cout << "Введите класс: ";
                int grade;
                cin >> grade;
                searchObj.setGrade(grade);
                clearInput();
                
                auto found = ring.search(searchObj);
                if (found != nullptr) {
                    cout << "\nШкольник найден в кольце:\n";
                    cout << setfill('=') << setw(60) << "=" << setfill(' ') << endl;
                    found->data.printHeader();
                    cout << " " << setfill('=') << setw(60) << "=" << setfill(' ') << endl;
                    found->data.printTable();
                    cout << " " << setfill('=') << setw(60) << "=" << setfill(' ') << endl;
                } else {
                    cout << "Школьник не найден в кольце.\n";
                }
                break;
            }
            case 5: {
                // Сортировать кольцо
                if (ring.isEmpty()) {
                    cout << "Кольцо пусто. Нечего сортировать.\n";
                    break;
                }
                ring.sort();
                cout << "Кольцо отсортировано успешно!\n";
                break;
            }
            case 6: {
                // Показать размер
                cout << "Размер кольца: " << ring.getSize() << " элементов.\n";
                break;
            }
            case 0: {
                cout << "До свидания!\n";
                break;
            }
            default: {
                cout << "Неверная опция!\n";
                break;
            }
        }
        
        if (choice != 0) {
            cout << "\nНажмите Enter для продолжения...";
            clearInput();
        }
    } while (choice != 0);
    
    return 0;
}

