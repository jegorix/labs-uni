// Структура содержит информацию о геометрических фигурах: площадь (число), название (указатель),
// вложенную структуру – периметр (вещественное число) и цвет (строка фиксированной длины). 
// Найти фигуры с площадью, меньше заданной. Удалить фигуры с заданным названием.

// Новицкий

// 14.03.2025

#include "validators.h"


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
    unsigned int square: 32;
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


Square* random_figures(int figure_count)
{

    Square* figure = malloc(figure_count * sizeof(Square));

    char* names[] = {"Круг", "Квадрат", "Прямоугольник", "Ромб", "Параллелограм", "Трапеция", "Треугольник", "Шестиугольник"};
    char* colors[] = {"Красный", "Оранжевый", "Желтый", "Зеленый", "Голубой", "Синий", "Фазан", "Черный", "Белый"};
    
    for(int i = 0; i < figure_count; i++)
    {
        char* rand_name = names[rand() % 8];
        figure[i].name = malloc(strlen(rand_name) + 1);
        strcpy(figure[i].name, rand_name);


        figure[i].square = (rand() % 1000) + 1;
        figure[i].perim.perm = 1.0 + ((float)rand() / RAND_MAX) * (1000.0 - 1.0);

        char* rand_color = colors[rand() % 9];
        figure[i].color = malloc(strlen(rand_color) + 1);
        strcpy(figure[i].color, rand_color);

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
        {
        return handle_figure_input(*figure_count);
        }

        default:
        {
        return random_figures(*figure_count);
        }

    }

}


void output_figures(Square* figure, int figure_count)
{

    printf("\nСписок фигур:\n");

    for(int i = 0; i < figure_count; i++)
    {
        printf("\nФигура № %d:\n", i + 1);
        printf("Имя: %s\n", figure[i].name);
        printf("Площадь: %d\n", figure[i].square);
        printf("Периметр: %.2f\n", figure[i].perim.perm);
        printf("Цвет: %s\n", figure[i].color);
        printf("\n");
    }

}


void find_figures(Square* figure, int figure_count, int limit_square)
{
    printf("Фигуры с площадью меньше, чем %d:\n", limit_square);
    for(int i = 0; i < figure_count; i++)
    {
        if(figure[i].square < limit_square)
        {
            printf("\nФигура № %d:\n", i + 1);
            printf("Имя: %s\n", figure[i].name);
            printf("Площадь: %d (<%d)\n", figure[i].square, limit_square);
            printf("Периметр: %.2f\n", figure[i].perim.perm);
            printf("Цвет: %s\n", figure[i].color);
            printf("\n");
        }
    }
}


void delete_figure(const char* fig_name, int* figure_count, Square** figure)
{

    for(int i = 0; i < *figure_count; i++)
    {

        if(strcmp(figure[i]->name, fig_name) == 0)
        {
            
            free(figure[i]->name);
            free(figure[i]->color);


            for(int j = i; j < (*figure_count) - 1; j++)
            {
                (*figure)[j] = (*figure)[j+1];
            }

            (*figure_count)--;

            if(*figure_count > 0)
            {
            *figure = realloc(*figure, (*figure_count) * sizeof(Square));
            printf("Фигура с именем '%s' успешна удалена \n", fig_name);
            }

            else
            {
                printf("Фигура с именем '%s' успешна удалена \n", fig_name);
                printf("Список фигур пуст!");
                free(*figure);
                return;
            }

        }

        else
        {
            printf("Фигура с именем '%s' не найдена.\n", fig_name);
            return;
        }
    }

    output_figures(*figure, *figure_count);

}



void user_action(Square* figures, int* figure_count)
{
    char user_choice[50];
    printf("Выберите действие:\n");
    printf("Найти фигуры с площадью, меньше заданной - 1\n");
    printf("Удалить фигуры с заданным названием - любая клавиша\n");

    fgets(user_choice, sizeof(user_choice), stdin);
    user_choice[strcspn(user_choice, "\n")] = '\0';

    switch(user_choice[0])
    {
        case '1':
        {
        printf("Введите площадь, относительно которой будет производиться поиск:\n");
        int limit_square = execute_verirfication(min_limit, max_limit);
        find_figures(figures, *figure_count, limit_square);
        }
        break;


        default:
        {
        char fig_name[50];
        printf("Введите имя удаляемой фигуры:\n");
        fgets(fig_name, sizeof(fig_name), stdin);
        fig_name[strcspn(fig_name, "\n")] = '\0';
        delete_figure(fig_name, figure_count, &figures);
        }
        break;

    }
    

}






int main(void)
{
    srand(time(NULL));
    int figure_count;
    Square* figures = identify_figures(&figure_count);

    output_figures(figures, figure_count);

    user_action(figures, &figure_count);

    free(figures);


    return 0;
}