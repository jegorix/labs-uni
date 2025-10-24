#include "include/Uchaschiysya.h"
#include "include/Shkolnik.h"
#include "include/Student.h"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;
const int MAX_OBJECTS = 5;
Shkolnik objects[MAX_OBJECTS];
int objectCount = 0;
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void printMenu() {
    const int width = 60;
    cout << "\n " << setfill('=') << setw(width) << "=" << setfill(' ') << endl;
    string title = "СИСТЕМА УПРАВЛЕНИЯ ШКОЛЬНИКАМИ";
    int padding = (width - 2 - (int)title.length()) / 2;
    cout << " |" << setw(padding) << " " << title << setw(width - 2 - padding - (int)title.length()) << " " << "|" << endl;
    cout << " " << setfill('=') << setw(width) << "=" << setfill(' ') << endl;
    cout << " |  1. Добавить школьника" << setw(width - 26) << " " << "|" << endl;
    cout << " |  2. Показать всех" << setw(width - 21) << " " << "|" << endl;
    cout << " |  3. Редактировать школьника" << setw(width - 30) << " " << "|" << endl;
    cout << " |  4. Удалить школьника" << setw(width - 25) << " " << "|" << endl;
    cout << " |  0. Выход" << setw(width - 13) << " " << "|" << endl;
    cout << " " << setfill('=') << setw(width) << "=" << setfill(' ') << endl;
    cout << " Выберите опцию: ";
}
void addObject() {
    if (objectCount >= MAX_OBJECTS) {
        cout << "Нельзя добавить больше объектов! Максимум достигнут.\n";
        return;
    }
    Shkolnik newObject;
    cout << "Введите данные школьника:\n";
    cin >> newObject;
    objects[objectCount] = newObject;
    objectCount++;
    cout << "Школьник добавлен успешно!\n";
}
void showAll() {
    cout << "\n" << setfill('=') << setw(60) << "=" << setfill(' ') << endl;
    cout << "                 ШКОЛЬНИКИ" << endl;
    cout << setfill('=') << setw(60) << "=" << setfill(' ') << endl;
    if (objectCount > 0) {
        objects[0].printHeader();
        cout << setfill('=') << setw(60) << "=" << setfill(' ') << endl;
        for (int i = 0; i < objectCount; i++) {
            objects[i].printTable();
        }
        cout << setfill('=') << setw(60) << "=" << setfill(' ') << endl;
    } else {
        cout << "Школьники не найдены." << endl;
    }
}
void editObject() {
    if (objectCount == 0) {
        cout << "Нет объектов для редактирования.\n";
        return;
    }
    cout << "\nДоступные школьники:\n";
    for (int i = 0; i < objectCount; i++) {
        cout << i + 1 << ". " << objects[i] << endl;
    }
    cout << "Выберите объект для редактирования: ";
    int index;
    cin >> index;
    clearInput();
    if (index < 1 || index > objectCount) {
        cout << "Неверный выбор.\n";
        return;
    }
    Shkolnik& obj = objects[index - 1];
    cout << "Текущие данные: " << obj << endl;
    cout << "Введите новые данные:\n";
    cin >> obj;
    cout << "Объект обновлен успешно!\n";
}
void deleteObject() {
    if (objectCount == 0) {
        cout << "Нет объектов для удаления.\n";
        return;
    }
    cout << "\nДоступные школьники:\n";
    for (int i = 0; i < objectCount; i++) {
        cout << i + 1 << ". " << objects[i] << endl;
    }
    cout << "Выберите объект для удаления: ";
    int index;
    cin >> index;
    if (index < 1 || index > objectCount) {
        cout << "Неверный выбор.\n";
        return;
    }
    cout << "Удаление: " << objects[index - 1] << endl;
    for (int i = index - 1; i < objectCount - 1; i++) {
        objects[i] = objects[i + 1];
    }
    objectCount--;
    cout << "Объект удален успешно!\n";
}
int main() {
    int choice;
    do {
        printMenu();
        cin >> choice;
        clearInput();
        switch (choice) {
            case 1:
                addObject();
                break;
            case 2:
                showAll();
                break;
            case 3:
                editObject();
                break;
            case 4:
                deleteObject();
                break;
            case 0:
                cout << "До свидания!\n";
                break;
            default:
                cout << "Неверная опция!\n";
        }
        cout << "\nНажмите Enter для продолжения...";
        clearInput();
    } while (choice != 0);
    return 0;
}