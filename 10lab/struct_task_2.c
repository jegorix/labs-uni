// Структура содержит информацию о геометрических фигурах: площадь (число), название (указатель),
// вложенную структуру – периметр (вещественное число) и цвет (строка фиксированной длины). 
// Найти фигуры с площадью, меньше заданной. Удалить фигуры с заданным названием.

// Новицкий

// 13.03.2025

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



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



enum
{
    max_limit = 2147483647,
    min_limit = 0,
};


typedef struct
{
    float perm;

} Perimiter;



typedef struct
{
    int square;
    char* name[20];
    Perimiter perm;
    char* color;
} Square;



void identify_figure_count()
{
    printf("Введите количество фигур:\n");
    // figure_count = execute_verification();

}






int main(void)
{

    identify_figure_count();


    // Square* circle = malloc(sizeof(Square) * 3);

    // circle[0].square = 26;
    // strcpy(circle[0].name, "Circle");

    // printf("%s\n", circle[0].name);


    return 0;
}