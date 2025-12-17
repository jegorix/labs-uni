#include "include/Shkolnik.h"
#include <iostream>
using namespace std;

const int MAX_OBJECTS = 5;
const int INPUT_COUNT = 3;
Shkolnik objects[MAX_OBJECTS];
Shkolnik copies[MAX_OBJECTS];
int objectCount = 0;

int main() {
    // Вводим вручную несколько (3) школьников
    for (int i = 0; i < INPUT_COUNT && i < MAX_OBJECTS; ++i) {
        cout << "Введите данные для школьника #" << i + 1 << ":\n";
        cin >> objects[i];
        ++objectCount;
    }

    // Копируем введённые объекты в другой массив,
    // чтобы продемонстрировать работу оператора присваивания
    for (int i = 0; i < objectCount; ++i) {
        copies[i] = objects[i];
    }


    // Выводим скопированные объекты в виде аккуратной таблицы
    if (objectCount > 0) {
        for (int i = 0; i < objectCount; ++i) {
            cout << copies[i];
        }
    }

    return 0;
}