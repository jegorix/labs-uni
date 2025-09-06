//
// Created by jegorix on 20.06.25.
//

#include "file_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "validators.h"
#include <time.h>

void open_existing_file(char** file_name, int* number_count)
{
    printf("\n╭────────────────────────────────────────────╮\n");
    printf("│ Введите имя существующего файла:          │\n");
    printf("╰────────────────────────────────────────────╯\n");
    printf("╰─> ");
    char* temp_name = user_name_input();

    FILE* file = fopen(temp_name, "rb");
    if (file == NULL)
    {
        printf("\n╭────────────────────────────────────────────╮\n");
        printf("│ Ошибка: файл не существует!               │\n");
        printf("╰────────────────────────────────────────────╯\n");
        free(temp_name);
        *file_name = NULL;
        *number_count = 0;
        return;
    }
    fclose(file);

    if (*file_name != NULL)
    {
        free(*file_name);
    }
    *file_name = temp_name;

    printf("\n╭────────────────────────────────────────────╮\n");
    printf("│ Введите количество чисел в файле:         │\n");
    printf("╰────────────────────────────────────────────╯\n");
    printf("╰─> ");
    *number_count = execute_verification(0, 2147483647);
}

void write_to_file_by_hand(char* file_name, int number_count)
{
    FILE* file = fopen(file_name, "wb");
    if (file != NULL)
    {
        for(int i = 0; i < number_count; i++)
        {
            printf("\n╭────────────────────────────────────╮\n");
            printf("│ Введите %d-е число для записи в файл: │\n", i+1);
            printf("╰────────────────────────────────────╯\n");
            printf("╰─> ");
            int number = execute_verification(-2147483647, 2147483647);
            fwrite(&number, sizeof(int), 1, file);
        }
        fclose(file);
    }
    printf("\n╭────────────────────────────────╮\n");
    printf("│ Целые числа успешно записаны!  │\n");
    printf("╰────────────────────────────────╯\n");
}

void write_to_file_by_random(char* file_name, int number_count)
{
    FILE* file = fopen(file_name, "wb");
    if (file != NULL)
    {
        for(int i = 0; i < number_count; i++)
        {
            int number = -1000000 + rand() % (1000000 * 2 + 1);
            fwrite(&number, sizeof(int), 1, file);
        }
        fclose(file);
    }
    printf("\n╭────────────────────────────────────────╮\n");
    printf("│ Целые случайные числа успешно записаны! │\n");
    printf("╰────────────────────────────────────────╯\n");
}

void file_data_output(char* file_name, int number_count)
{
    printf("\n╭────────────────────────────╮\n");
    printf("│ Ваши числа:                │\n");
    printf("╰────────────────────────────╯\n");
    FILE* file_r = fopen(file_name, "rb");
    if (file_r != NULL)
    {
        for(int i = 0; i < number_count; i++)
        {
            int number;
            fread(&number, sizeof(int), 1, file_r);
            printf("╭────────────╮\n");
            printf("│ %10d │\n", number);
            printf("╰────────────╯\n");
        }
        fclose(file_r);
    }
}

void fill_file_menu(char** file_name, int* number_count)
{
    srand(time(NULL));

    printf("\n╭────────────────────────────────────────────╮\n");
    printf("│ Введите имя файла:                        │\n");
    printf("╰────────────────────────────────────────────╯\n");
    printf("╰─> ");
    char* temp_name = user_name_input();

    if (*file_name != NULL)
    {
        free(*file_name); // Освобождаем старую память
    }
    *file_name = temp_name;

    printf("\n╭────────────────────────────────────────────╮\n");
    printf("│ Введите количество целых чисел для записи: │\n");
    printf("╰────────────────────────────────────────────╯\n");
    printf("╰─> ");
    *number_count = execute_verification(0, 2147483647);

    printf("\n╭────────────────────────────────────────────╮\n");
    printf("│ Выберите способ заполнения файла:          │\n");
    printf("│ 1 - Вручную                               │\n");
    printf("│ 2 - Случайными числами                    │\n");
    printf("╰────────────────────────────────────────────╯\n");
    printf("╰─> ");
    int choice = execute_verification(1, 2);

    switch (choice)
    {
        case 1:
            write_to_file_by_hand(*file_name, *number_count);
            break;
        case 2:
            write_to_file_by_random(*file_name, *number_count);
            break;
    }

    printf("\n╭────────────────────────────────────────────╮\n");
    printf("│ Вывести содержимое файла?                 │\n");
    printf("│ 1 - Да                                    │\n");
    printf("│ Любая другая клавиша - Нет                 │\n");
    printf("╰────────────────────────────────────────────╯\n");
    printf("╰─> ");
    char* user_choice = user_name_input();
    if (user_choice[0] == '1')
    {
        file_data_output(*file_name, *number_count);
    }

    free(user_choice);
}

void find_max_length_sequence(char* file_name, int number_count)
{
    FILE* file = fopen(file_name, "rb");
    if (file == NULL)
    {
        printf("\n╭────────────────────────────────────────────╮\n");
        printf("│ Ошибка открытия файла!                    │\n");
        printf("╰────────────────────────────────────────────╯\n");
        return;
    }

    int prev_number, current_number;
    int current_sequence = 1;
    int max_sequence = 1;
    int that_elem;

    if (number_count == 0)
    {
        printf("\n╭────────────────────────────────────────────╮\n");
        printf("│ Файл пуст!                                │\n");
        printf("╰────────────────────────────────────────────╯\n");
        fclose(file);
        return;
    }

    fread(&prev_number, sizeof(int), 1, file);
    that_elem = prev_number;

    printf("\n╭────────────────────────────╮\n");
    printf("│ Числа в файле:            │\n");
    printf("╰────────────────────────────╯\n");
    printf("%d ", prev_number);
    printf("\n");

    for (int i = 1; i < number_count; i++)
    {
        fread(&current_number, sizeof(int), 1, file);
        printf("%d ", current_number);
        printf("\n");

        if (prev_number == current_number)
        {
            current_sequence++;
            if (current_sequence > max_sequence)
            {
                max_sequence = current_sequence;
                that_elem = current_number;
            }
        }
        else
        {
            current_sequence = 1;
        }
        prev_number = current_number;
    }

    printf("\n╭────────────────────────────────────────────╮\n");
    printf("│ Самая длинная последовательность: %3d      │\n", max_sequence);
    printf("│ Элемент: %10d                    │\n", that_elem);
    printf("╰────────────────────────────────────────────╯\n");

    fclose(file);
}

void zero_even_positions(char* file_name, int number_count)
{
    FILE* file = fopen(file_name, "r+b");
    if (file == NULL)
    {
        printf("\n╭────────────────────────────────────────────╮\n");
        printf("│ Ошибка открытия файла!                    │\n");
        printf("╰────────────────────────────────────────────╯\n");
        return;
    }

    if (number_count == 0)
    {
        printf("\n╭────────────────────────────────────────────╮\n");
        printf("│ Файл пуст!                                │\n");
        printf("╰────────────────────────────────────────────╯\n");
        fclose(file);
        return;
    }

    printf("\n╭────────────────────────────╮\n");
    printf("│ Числа до зануления:       │\n");
    printf("╰────────────────────────────╯\n");

    for (int i = 0; i < number_count; i++)
    {
        int current_number;
        fread(&current_number, sizeof(int), 1, file);
        printf("╭────────────╮\n");
        printf("│ %10d │\n", current_number);
        printf("╰────────────╯\n");

        if (i % 2 == 0)
        {
            current_number = 0;
            fseek(file, -sizeof(int), SEEK_CUR);
            fwrite(&current_number, sizeof(int), 1, file);
        }
    }

    rewind(file);

    printf("\n╭────────────────────────────╮\n");
    printf("│ Числа после зануления:    │\n");
    printf("╰────────────────────────────╯\n");

    for (int i = 0; i < number_count; i++)
    {
        int current_number;
        fread(&current_number, sizeof(int), 1, file);
        printf("%d ", current_number);
        printf("\n");
    }

    printf("\n╭────────────────────────────────────────────╮\n");
    printf("│ Элементы на чётных позициях занулены!     │\n");
    printf("╰────────────────────────────────────────────╯\n");

    fclose(file);
}

void hybrid_sort(char* file_name, int number_count)
{
    FILE* file = fopen(file_name, "r+b");
    if (file == NULL)
    {
        printf("\n╭────────────────────────────────────────────╮\n");
        printf("│ Ошибка открытия файла!                    │\n");
        printf("╰────────────────────────────────────────────╯\n");
        return;
    }

    if (number_count == 0)
    {
        printf("\n╭────────────────────────────────────────────╮\n");
        printf("│ Файл пуст!                                │\n");
        printf("╰────────────────────────────────────────────╯\n");
        fclose(file);
        return;
    }

    printf("\n╭────────────────────────────╮\n");
    printf("│ Числа до сортировки:      │\n");
    printf("╰────────────────────────────╯\n");

    rewind(file);
    for (int i = 0; i < number_count; i++)
    {
        int number;
        fread(&number, sizeof(int), 1, file);
        printf("╭────────────╮\n");
        printf("│ %10d │\n", number);
        printf("╰────────────╯\n");
    }

    int current_number;
    int zero_pos = 0;
    int even_pos = 0;
    int odd_pos = number_count - 1;

    while (zero_pos <= odd_pos)
    {
        fseek(file, zero_pos * sizeof(int), SEEK_SET);
        fread(&current_number, sizeof(int), 1, file);

        if (current_number % 2 == 0 && current_number != 0)
        {
            if (zero_pos != even_pos)
            {
                int temp;
                fseek(file, even_pos * sizeof(int), SEEK_SET);
                fread(&temp, sizeof(int), 1, file);
                fseek(file, zero_pos * sizeof(int), SEEK_SET);
                fwrite(&temp, sizeof(int), 1, file);
                fseek(file, even_pos * sizeof(int), SEEK_SET);
                fwrite(&current_number, sizeof(int), 1, file);
            }
            even_pos++;
            zero_pos++;
        }
        else if (current_number == 0)
        {
            zero_pos++;
        }
        else
        {
            if (current_number % 2 != 0)
            {
                if (zero_pos != odd_pos)
                {
                    int temp;
                    fseek(file, odd_pos * sizeof(int), SEEK_SET);
                    fread(&temp, sizeof(int), 1, file);
                    fseek(file, zero_pos * sizeof(int), SEEK_SET);
                    fwrite(&temp, sizeof(int), 1, file);
                    fseek(file, odd_pos * sizeof(int), SEEK_SET);
                    fwrite(&current_number, sizeof(int), 1, file);
                }
            }
            odd_pos--;
        }
    }

    printf("\n╭────────────────────────────╮\n");
    printf("│ Числа после сортировки:   │\n");
    printf("╰────────────────────────────╯\n");

    rewind(file);
    for (int i = 0; i < number_count; i++)
    {
        int number;
        fread(&number, sizeof(int), 1, file);
        printf("%d ", number);
        printf("\n");
    }

    printf("\n╭────────────────────────────────────────────╮\n");
    printf("│ Файл отсортирован: чётные - нули - нечётные │\n");
    printf("╰────────────────────────────────────────────╯\n");

    fclose(file);
}