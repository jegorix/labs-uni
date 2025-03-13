// Найти и вывести остаток от деления целого числа на 2, не выполняя деления и не используя операцию взятия остатка от деления.
// Новицкий
// 11.03.2025

#include <stdio.h>
#include <time.h>
#include <stdlib.h>


enum
{
    max_limit = 2147483647,
    min_limit = -2147483647,
    rand_max_limit = 1000000,
    rand_min_limit = -1000000,
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






int identify_user_choice()
{
    char input[256];
    int number;
    printf("Введите целое число самостоятельно - 1. Выбрать случайное - любая клавиша:\n");
    fgets(input, 256, stdin);


    switch(input[0])
    {
        case '1':
        printf("Введите число:\n");
        number = execute_verirfication(min_limit, max_limit);
        break;

        default:
        number = rand_min_limit + rand() % (rand_max_limit * 2 + 1);
        break;

    }
    return number;

}






int main(void)
{
   
    srand(time(NULL));
    int user_number = identify_user_choice();
    printf("YOur number = %d\n", user_number);


    return 0;
}

// последний бит 1 или 0 посмотреть