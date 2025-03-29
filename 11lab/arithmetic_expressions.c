//
// Created by Macbook on 29.03.25.
//

#include "arithmetic_expressions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "validators.h"

char* make_file()
    {
  char* file_name = malloc(50) ;
  printf("Введите имя файла: ");
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
    printf("Введите выражение:\n");
    fgets(input, 256, stdin);
    return input;
}


void add_data(char* file_name, char* user_input)
{
    FILE* file = fopen(file_name, "a+");
    if(file == NULL)
    {
        printf("Не удалось открыть файл!\n");
        return;
    }

    fputs(user_input, file);
    fclose(file);

}



void create_expressions(char* file_name)
        {
  printf("Сколько арифметических выражений вы хотите записать?");
  int expressions_count = execute_verification(0, max_limit);
  printf("Введите арифметическое выражение, используя ' -, +, *, / и скобки () ' ");
  for(int i = 0; i < expressions_count; i++)
    {
    printf("%d-ое выражение:\n", i+1);
    char* user_expression = get_words();
    add_data(file_name, user_expression);
    }
        }






void make_or_choose_file()
    {
  char user_input[50];
  printf("Выберите действие:\n");
  printf("Создать новый файл и работать в нем - 1:\n");
  printf("Выбрать существующий файл и работать в нем - 2:\n");
  fgets(user_input, 50, stdin);
  char* file_name;

  switch (user_input[0])
  {
    case '1':
       file_name = make_file();
       create_expressions(file_name);
  }


    }