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





void create_expressions(char* file_name, int* expressions_count)
        {
  printf("Сколько арифметических выражений вы хотите записать?");
  *expressions_count = execute_verification(0, max_limit);
  printf("Введите арифметическое выражение, используя ' -, +, *, / и скобки () ' ");
  for(int i = 0; i < *expressions_count; i++)
    {
    printf("%d-ое выражение:\n", i+1);
    char* user_expression = get_words();
    user_expression[strcspn(user_expression, "\n")] = 0;
    add_data(file_name, user_expression);
    }
        }

void extract_expressions(char* file_name, int expressions_count)
            {
  FILE* file = fopen(file_name, "r");
  if(file == NULL)
    {
      printf("Не удалось открыть файл!\n");
      return;
    }


  char* buffer = malloc(256 * sizeof(char));
  for(int i = 0; i < expressions_count; i++)
    {
       fgets(buffer, 256, file);
       buffer[strcspn(buffer, "\n")] = 0;
       parse_expressions(buffer);
//       printf("%s\n", buffer);

    }
    free(buffer);

fclose(file);
            }


 int count_sentence(char* file_name)
                {
   FILE* file = fopen(file_name, "r");
   int sentence_count = 0;
   char ch;
   while((ch = fgetc(file)) != EOF)
     {
        if(ch == '\0' || ch == '\n' || ch == '=')
          {

          sentence_count++;
          }
     }

    printf("%d\n", sentence_count);
     fclose(file);
     return sentence_count;
                }


void make_or_choose_file()
    {
  char user_input[50];
  printf("Выберите действие:\n");
  printf("Создать новый файл и работать в нем - 1:\n");
  printf("Выбрать существующий файл и работать в нем - 2:\n");
  fgets(user_input, 50, stdin);
  char* file_name;
  int expressions_count;

  switch (user_input[0])
  {
    case '1':
       file_name = make_file();
       create_expressions(file_name, &expressions_count);
       extract_expressions(file_name, expressions_count);
       free(file_name);
       break;

     case '2':
       file_name = malloc(50);
       printf("Введите имя существующего файла: ");
       fgets(file_name, 50, stdin);
       file_name[strcspn(file_name, "\n")] = 0;
      expressions_count = count_sentence(file_name);
      extract_expressions(file_name, expressions_count);

      free(file_name);
      break;



  }


    }