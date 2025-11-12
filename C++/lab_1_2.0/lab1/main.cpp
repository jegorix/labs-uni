#include <iostream>
#include "string_subtractor.h"

int main() {
    int n;
    std::cout << "Введите количество строк: ";
    std::cin >> n;
    std::cin.ignore(); // убрать '\n' после числа

    StringSub* arr = new StringSub[n];

    std::cout << "Введите строки:\n";
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];   // используем перегруженный оператор >>
    }

    std::cout << "\nВы ввели:\n";
    for (int i = 0; i < n; ++i)
        std::cout << "  " << i + 1 << ") \"" << arr[i]
                  << "\" (длина " << arr[i].length() << ")\n";

    if (n > 0) {
        int result = arr[0].length();
        std::cout << "\nВычисление: " << arr[0].length();
        for (int i = 1; i < n; ++i) {
            result -= arr[i].length();
            std::cout << " - " << arr[i].length();
        }
        std::cout << " = " << result << "\n";

        std::cout << "Результат вычитания длин строк: " << result << "\n";
    }

    delete[] arr;
    return 0;
}