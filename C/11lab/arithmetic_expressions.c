//
// Created by Macbook on 29.03.25.
//

#include "arithmetic_expressions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "validators.h"
#include "parse_&_calculate_expressions.h"

char* make_file()
{
    char* file_name = malloc(50) ;
    printf(
            "\n╭─────────────────────────────────────╮\n"
            "│         Введите имя файла           │\n"
            "╰─────────────────────────────────────╯\n"
            "╰─> "
    );


    fgets(file_name, 50, stdin);
    file_name[strcspn(file_name, "\n")] = 0;
    int len = strlen(file_name);
    if(len < 4 || strncmp(file_name + len - 4, ".txt", 4) != 0)
    {
        strcat(file_name, ".txt");
    }

    return file_name;
}



char* get_words()
{
    char* input = malloc(256 * sizeof(char));
    printf("\n");
    printf(
          "\n╭─────────────────────────────────────╮\n"
            "│         Введите выражение:          │\n"
            "╰─────────────────────────────────────╯\n"
            "╰─> "
    );
    fgets(input, 256, stdin);
    input[strcspn(input, "\n")] = 0;
    return input;
}


void add_data(char* file_name, char* user_input)
{
    FILE* file = fopen(file_name, "a");
    if(file == NULL)
    {
        printf(
              "\n╭─────────────────────────────────────╮\n"
                "│       Не удалось открыть файл!      │\n"
                "╰─────────────────────────────────────╯\n"
                "╰─> "
        );
        return;
    }

    fputs(user_input, file);
    fputc('\n', file);
    fclose(file);

}





void create_expressions(char* file_name, int* expressions_count)
{
    printf(
            "\n╭────────────────────────────────────────────────────────────╮\n"
            "│ Сколько арифметических выражений вы хотите записать?       │\n"
            "╰────────────────────────────────────────────────────────────╯\n"
            "╰─> "
    );
    *expressions_count = execute_verification(0, max_limit);

    printf(
            "\n╭────────────────────────────────────────────────────────────╮\n"
            "│ Введите арифметическое выражение, используя -, +, *, / и ()│\n"
            "╰────────────────────────────────────────────────────────────╯\n"
    );

    for (int i = 0; i < *expressions_count; i++)
    {
        printf(
                "\n╭────────────────────────────────────────────────────────────╮\n"
                "│                    %d-ое выражение:                         │\n"
                "╰────────────────────────────────────────────────────────────╯\n"
                "╰─> ", i + 1
        );
        char* user_expression = get_words();
        user_expression[strcspn(user_expression, "\n")] = 0;
        add_data(file_name, user_expression);
        free(user_expression);
    }
}




void extract_expressions(char* file_name, int* expressions_count, char*** expressions)
{
    char line[256];
    *expressions_count = 0;
    FILE* file = fopen(file_name, "r");

    if (file == NULL)
    {
        printf(
                "\n╭─────────────────────────────────────╮\n"
                "│       Не удалось открыть файл!      │\n"
                "╰─────────────────────────────────────╯\n"
                "╰─> "
        );
        return;
    }

    while (fgets(line, 256, file))
    {
        (*expressions_count)++;
    }

    fseek(file, 0, SEEK_SET);
    *expressions = malloc((*expressions_count) * sizeof(char*));

    for (int i = 0; i < *expressions_count; i++)
    {
        fgets(line, 256, file);
        line[strcspn(line, "\n")] = 0;
        (*expressions)[i] = strdup(line);
    }

    fclose(file);
}






void calculate_expressions(int expressions_count, char** expressions)
{
    FILE* file_output = fopen("results/output.txt", "w");

    if (file_output == NULL)
    {
        printf(
                "\n╭────────────────────────────────────────╮\n"
                "│   Не удалось открыть файл output.txt   │\n"
                "╰────────────────────────────────────────╯\n"
                "╰─> "
        );
        return;
    }

    for (int i = 0; i < expressions_count; i++)
    {
        int error_pos;
        int error_code = check_for_errors(expressions[i], &error_pos);

        if (error_code != 0)
        {
            if (error_code == 1)
            {
                fprintf(file_output, "Ошибка в позиции %d: несбалансированные скобки\n", error_pos);
            }
            else if (error_code == 2)
            {
                fprintf(file_output, "Ошибка в позиции %d: синтаксическая ошибка\n", error_pos);
            }
            else if (error_code == 4)
            {
                fprintf(file_output, "Ошибка в позициях %d и %d: деление на ноль\n", error_pos, error_pos + 1);
            }
            else
            {
                fprintf(file_output, "Ошибка в позиции %d: недопустимый символ\n", error_pos);
            }
            continue;
        }

        char rpn[256] = "";
        convert_to_rpn(expressions[i], rpn);
        double result = evaluate_rpn(rpn);
        fprintf(file_output, "Результат выражения %d: %.2f\n", i + 1, result);
    }

    fclose(file_output);

    printf(
            "\n╭────────────────────────────────────────────────────╮\n"
            "│ Обработка завершена. Результаты в файле output.txt │\n"
            "╰────────────────────────────────────────────────────╯\n"
    );
}





void make_or_choose_file()
{

    printf(
            "\n╭────────────────────────────────────────────────────────────╮\n"
            "│ Выберите действие:                                         │\n"
            "│ 1 - Создать новый файл и работать в нем                    │\n"
            "│ 2 - Выбрать существующий файл и работать в нем             │\n"
            "╰────────────────────────────────────────────────────────────╯\n"
            "╰─> "
    );
    char user_input = fgetch();

    char* file_name;
    int expressions_count;
    char** expressions;

    switch (user_input)
    {
        case '1':
            file_name = make_file();
            create_expressions(file_name, &expressions_count);
            extract_expressions(file_name, &expressions_count, &expressions);
            calculate_expressions(expressions_count, expressions);
            free(file_name);
            break;

        case '2':
            file_name = malloc(50);
            printf(
                    "\n╭───────────────────────────────────────╮\n"
                    "│  Введите имя существующего файла:     │\n"
                    "╰───────────────────────────────────────╯\n"
                    "╰─> "
            );
            fgets(file_name, 50, stdin);
            file_name[strcspn(file_name, "\n")] = 0;
            extract_expressions(file_name, &expressions_count, &expressions);
            calculate_expressions(expressions_count, expressions);
            free(file_name);
            break;
    }
}