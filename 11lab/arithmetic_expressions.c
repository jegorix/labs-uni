//
// Created by Macbook on 29.03.25.
//

#include "arithmetic_expressions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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