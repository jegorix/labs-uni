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



float execute_verirfication_float(float min_limit, float max_limit)
{
    char input[100];
    float number;
    char symbol;
     
    while(1)
    {
        if(fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("Ошибка ввода! Попробуйте еще раз!\n");
            continue;
        }

        if (sscanf(input, "%f %c", &number, &symbol) != 1)
        {
            printf("Ошибка ввода! Введите число с плавающей запятой:\n");
            continue;
        }

        if (number > max_limit || number < min_limit)
        {
            printf("Ошибка ввода! Введите число из диапазона [%.2f, %.2f]:\n", min_limit, max_limit);
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
    char* name;
    Perimiter perim;
    char* color;
} Square;



Square* handle_figure_input(int figure_count)
{
    Square* figure = malloc(sizeof(Square) * figure_count); // create figures array

    for(int i = 0; i < figure_count; i++)
    {
        char* fig_name = malloc(256 * sizeof(char));
        printf("Введите имя вашей фигуры № %d:\n", i + 1);
        fgets(fig_name, 256, stdin);
        fig_name[strcspn(fig_name, "\n")] = '\0';
        figure[i].name = malloc(strlen(fig_name) + 1);
        strcpy(figure[i].name, fig_name);
        free(fig_name);

        printf("Введите площадь фигуры '%s':\n", figure[i].name);
        figure[i].square = execute_verirfication(min_limit, max_limit);

        printf("Введите периметр фигуры '%s'\n", figure[i].name);
        figure[i].perim.perm = execute_verirfication_float(min_limit, max_limit);

        printf("Введите цвет фигуры '%s':\n", figure[i].name);
        char* fig_color = malloc(256 * sizeof(char));
        fgets(fig_color, 256, stdin);
        fig_color[strcspn(fig_color, "\n")] = '\0';
        figure[i].color = malloc(strlen(fig_color) + 1);
        strcpy(figure[i].color, fig_color);
        free(fig_color);

    }

    return figure;

    
}



Square* identify_figures(int* figure_count)
{
    char user_choice[50];
    printf("Введите количество фигур:\n");
    *figure_count = execute_verirfication(min_limit, max_limit);
    printf("Ввести фигуры вручную - 1. Рандомные фигуры - любая клавиша:\n");
    fgets(user_choice, sizeof(user_choice), stdin);

    switch(user_choice[0])
    {
        case '1':
        return handle_figure_input(*figure_count);

        // default:
        // Square* figures = random_figures(figure_count);
        // return figures;

    }

}


void output_figures(Square* figure, int figure_count)
{

    for(int i = 0; i < figure_count; i++)
    {
        printf("\nФигура № %d:\n", i + 1);
        printf("Имя: %s\n", figure[i].name);
        printf("Площадь: %d\n", figure[i].square);
        printf("Периметр: %.2f\n", figure[i].perim.perm);
        printf("\n");
    }

}




int main(void)
{
    int figure_count;
    Square* figures = identify_figures(&figure_count);
    output_figures(figures, figure_count);

    // Square* circle = malloc(sizeof(Square) * 3);

    // circle[0].square = 26;
    // strcpy(circle[0].name, "Circle");

    // printf("%s\n", circle[0].name);


    return 0;
}