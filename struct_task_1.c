// Найти и вывести остаток от деления целого числа на 2, не выполняя деления и не используя операцию взятия остатка от деления.
// Новицкий
// 11.03.2025

#include <stdio.h>
#include <time.h>


enum
{
    max_limit = 2147483647,
    min_limit = 0
};


int execute_verirfication(int min_limit, int max_limit)
{
    char input[100];
    int number;
    char symbol;
     
    while(1)
    {
        if(fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("Ошибка ввода! Попробуйте еще раз!\n");
            continue;
        }

        if (sscanf(input, "%d %c", &number, &symbol) != 1)
        {
            printf("Ошибка ввода! Введите целое число:\n");
            continue;
        }

        if (number > max_limit || number < min_limit)
        {
            printf("Ошибка ввода! Введите число из диапазона [%d, %d]:\n", min_limit, max_limit);
            continue;
        }

        return number;

    }

}





void identify_user_choice()
{
    printf("Введите целое число самостоятельно - 1. Выбрать случайное - любая клавиша");
    int user_choice = execute_verirfication(min_limit, max_limit);
    printf("Your choice: %d", user_choice);

}






int main(void)
{
    identify_user_choice();


    return 0;
}

// последний бит 1 или 0 посмотреть