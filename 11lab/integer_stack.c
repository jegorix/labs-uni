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







void create_stacks()
{
printf("Введите размер первого стека:\n");
int first_stack_size = execute_verification(min_limit, max_limit);
OBJ* top_one = NULL;
top_one = declare_stack(first_stack_size, top_one, 1);
stack_print(top_one, 1);


printf("Введите размер второго стека:\n");
int second_stack_size = execute_verification(min_limit, max_limit);
OBJ* top_two = NULL;
top_two = declare_stack(second_stack_size, top_two, 2);
stack_print(top_two, 2);

}


