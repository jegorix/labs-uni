//
// Created by Macbook on 28.03.25.
//

#include "integer_stack.h"
#include <stdio.h>
#include <stdlib.h>
#include "validators.h"

OBJ* stack_push(OBJ* top, int data)
    {
  OBJ* temp = malloc(sizeof(OBJ));
  temp->data = data;
  temp->next = top;
  return temp;
    }


OBJ* stack_pop(OBJ* top)
        {
  if (top == NULL)
    {
    return top;
    }
    OBJ* next_elem = top->next;
    free(top);
    return next_elem;
        }


 OBJ* declare_stack(int stack_size, OBJ* top, int stack_number)
  {

      for(int i = 0; i < stack_size; i++)
      {

        printf("Введите данные %d-го элемента стека-%d:\n", i + 1, stack_number);
        int regular_data = execute_verification(min_limit, max_limit);
        top = stack_push(top, regular_data);

      }
      return top;

  }




void stack_print(OBJ* top, int stack_number)
      {
  printf("Содержимое Стека-%d:\n", stack_number);

  if (top == NULL)
    {
    printf("Стек пуст\n");
    return;
    }

  OBJ* current = top;
  while(current != NULL)
    {

    printf("%d\n", current->data);
    current = current->next;

    }
    printf("\n");
      }




 void special_stack_output(OBJ* top_1, OBJ* top_2)
          {
     printf("Все элементы первого стека, которые есть во втором стеке:\n");
     OBJ* current_1 = top_1;
     OBJ* current_2 = top_2;

     while(current_1 != NULL)
       {
       while(current_2 != NULL)
         {
       if(current_1->data == current_2->data)
           {
           printf("%d\n", current_1->data);
           }
           current_2 = current_2->next;
         }
         current_1 = current_1->next;
         current_2 = top_2;
       }


          }





void stacks_operations(OBJ* top_1, OBJ* top_2)
    {
  int running = 1;

  while(running)
    {
    printf("\n");
  char user_input[50];
    printf("Выберите операцию:\n");
    printf("Содержимое первого стека: - 1\n");
    printf("Содержимое второго стека: - 2\n");
    printf("Содержимое обоих стеков: - 3\n");
    printf("Все элементы первого стека, которые есть во втором стеке: - 4\n");
    printf("Выход - любая другая клавиша\n");

    fgets(user_input, 50, stdin);

  switch(user_input[0])
  {
    case '1':
    {
      stack_print(top_1, 1);
    }break;

    case '2':
    {
      stack_print(top_2, 2);
    }break;

    case '3':
    {
      stack_print(top_1, 1);
      stack_print(top_2, 2);
    }break;

    case '4':
       {
       special_stack_output(top_1, top_2);
       }break;

    default:
    {
      running = 0;
    }break;

  }

  }

    }



void create_stacks()
{
  printf("Введите размер первого стека:\n");
  int first_stack_size = execute_verification(min_limit, max_limit);
  OBJ* top_one = NULL;
  top_one = declare_stack(first_stack_size, top_one, 1);



  printf("Введите размер второго стека:\n");
  int second_stack_size = execute_verification(min_limit, max_limit);
  OBJ* top_two = NULL;
  top_two = declare_stack(second_stack_size, top_two, 2);

  stacks_operations(top_one, top_two);


}


