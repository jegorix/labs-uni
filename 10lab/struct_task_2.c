// Структура содержит информацию о геометрических фигурах: площадь (число), название (указатель),
// вложенную структуру – периметр (вещественное число) и цвет (строка фиксированной длины). 
// Найти фигуры с площадью, меньше заданной. Удалить фигуры с заданным названием.

// Новицкий

// 13.03.2025

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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



// int execute_verification()





int main(void)
{

    identify_figure_count();


    // Square* circle = malloc(sizeof(Square) * 3);

    // circle[0].square = 26;
    // strcpy(circle[0].name, "Circle");

    // printf("%s\n", circle[0].name);


    return 0;
}