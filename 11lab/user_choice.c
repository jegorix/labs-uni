//
// Created by Macbook on 28.03.25.
//

#include "user_choice.h"
#include "integer_stack.h"
#include <stdio.h>
#include <string.h>

void user_choice_action()
    {
      char user_input[50];
      printf("Выберите номер задачи:\n");
      printf("Задача № 1 - введите цифру 1\n");
      printf("Задача № 2 - введите цифру 2\n");
      printf("Задача № 3 - любая другая клавиша \n");

      fgets(user_input, 50, stdin);

      switch(user_input[0])
      {
        case '1':
          {
            create_stacks();
          }break;

        case '2':
          {
          return;
          }break;

        default:
          {
          return;
          }

      }



    }
