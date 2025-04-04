//
// Created by Macbook on 28.03.25.
//

#include "user_choice.h"
#include "integer_stack.h"
#include <stdio.h>
#include <string.h>
#include "sort_third_stack.h"
#include "arithmetic_expressions.h"
void user_choice_action()
    {
  int exit = 0;
  while(!exit)
  {
      char user_input[50];

      printf("Выберите номер задачи:\n");
      printf("Задача № 1 - введите цифру 1\n");
      printf("Задача № 2 - введите цифру 2\n");
      printf("Задача № 3 - введите цифру 3\n");
      printf("Продолжить - введите цифру 4\n");
      printf("Выход - любая другая клавиша \n");

      fgets(user_input, 50, stdin);


      switch(user_input[0])
      {
        case '1':
          {
            create_stacks();
          }break;

        case '2':
          {
          build_third_stack();
          }break;

        case '3':
        {
          make_or_choose_file();
        }break;

         case '4':
           continue;

        default:
          {
          exit = 1;
          return;
          }

      }


}
    }
