#include "file_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "filework_menu.h"

int choose_file_operation(char** file_name, int* number_count)
{
    printf("\n╭────────────────────────────────────────────╮\n");
    printf("│ Выберите действие:                         │\n");
    printf("│ 1 - Создать новый файл                     │\n");
    printf("│ 2 - Открыть существующий файл              │\n");
    printf("╰────────────────────────────────────────────╯\n");
    printf("╰─> ");
    int choice = execute_verification(1, 2);

    if (*file_name != NULL)
    {
        free(*file_name);
        *file_name = NULL;
    }

    if (choice == 1)
    {
        fill_file_menu(file_name, number_count);
        return (*file_name != NULL && *number_count > 0) ? 0 : 1;
    }
    else
    {
        open_existing_file(file_name, number_count);
        return (*file_name != NULL && *number_count > 0) ? 0 : 1;
    }
}

void file_tasks_menu(char** file_name, int* number_count)
{
    while (1)
    {
        printf("\n╭─────────────────────────────────────────────────────────────────╮\n");
        printf("│ Выберите операцию с файлом:                                     │\n");
        printf("│ 1 - Заполнить файл целыми числами                               │\n");
        printf("│ 2 - Найти самую длинную последовательность равных элементов     │\n");
        printf("│ 3 - Занулить элементы на чётных позициях                        │\n");
        printf("│ 4 - Отсортировать: чётные слева, нули в центре, нечётные справа │\n");
        printf("│ 0 - Выход в главное меню                                        │\n");
        printf("╰─────────────────────────────────────────────────────────────────╯\n");
        printf("╰─> ");

        int choice = execute_verification(0, 4);

        switch (choice)
        {
            case 1:
                printf("\n╭────────────────────────────────────────────────────────────╮\n");
                printf("│ Задача 1: Заполнить файл целыми числами                    │\n");
                printf("╰────────────────────────────────────────────────────────────╯\n");
                if (*file_name != NULL)
                {
                    free(*file_name);
                    *file_name = NULL;
                }
                fill_file_menu(file_name, number_count);
                break;

            case 2:
                printf("\n╭───────────────────────────────────────────────────────────────────╮\n");
                printf("│ Задача 2: поиск самой длинной последовательности равных элементов │\n");
                printf("╰───────────────────────────────────────────────────────────────────╯\n");
                if (choose_file_operation(file_name, number_count) == 0)
                {
                    find_max_length_sequence(*file_name, *number_count);
                }
                else
                {
                    printf("\n╭────────────────────────────────────────────╮\n");
                    printf("│ Операция отменена: файл не выбран.         │\n");
                    printf("╰────────────────────────────────────────────╯\n");
                }
                break;

            case 3:
                printf("\n╭────────────────────────────────────────────────────────────╮\n");
                printf("│ Задача 3: зануление элементов на чётных позициях           │\n");
                printf("╰────────────────────────────────────────────────────────────╯\n");
                if (choose_file_operation(file_name, number_count) == 0)
                {
                    zero_even_positions(*file_name, *number_count);
                }
                else
                {
                    printf("\n╭────────────────────────────────────────────╮\n");
                    printf("│ Операция отменена: файл не выбран.         │\n");
                    printf("╰────────────────────────────────────────────╯\n");
                }
                break;

            case 4:
                printf("\n╭────────────────────────────────────────────────────────────╮\n");
                printf("│ Задача 4: сортировка чётные - нули - нечётные              │\n");
                printf("╰────────────────────────────────────────────────────────────╯\n");
                if (choose_file_operation(file_name, number_count) == 0)
                {
                    hybrid_sort(*file_name, *number_count);
                }
                else
                {
                    printf("\n╭────────────────────────────────────────────╮\n");
                    printf("│ Операция отменена: файл не выбран.         │\n");
                    printf("╰────────────────────────────────────────────╯\n");
                }
                break;

            case 0:
                printf("\n╭────────────────────────────╮\n");
                printf("│ Возврат в главное меню...  │\n");
                printf("╰────────────────────────────╯\n");
                if (*file_name != NULL)
                {
                    free(*file_name);
                    *file_name = NULL;
                }
                return;

            default:
                printf("\n╭───────────────────────────────────╮\n");
                printf("│ Неверный выбор. Попробуйте снова. │\n");
                printf("╰───────────────────────────────────╯\n");
                break;
        }
    }
}