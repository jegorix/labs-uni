//
// Created by jegorix on 24.04.25.
//

#include "validators.h"

#include "validators.h"


int execute_verification(int min_limit, int max_limit)
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


char* user_name_input(void)
{
    char* str = NULL;
    char ch;
    int length = 0;
    int capacity = 10;

    str = malloc(sizeof(char) * capacity);

    while((ch = getchar()) != '\n')
    {
        if(length + 1 >= capacity)
        {
            capacity *= 2;
            str = realloc(str, capacity * sizeof(char));
        }

        str[length++] = ch;
    }
    str[length] = '\0';

    return str;
}

void clearScreen()
{
    printf("\033c");
    fflush(stdout);
}