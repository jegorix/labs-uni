//
// Created by Macbook on 28.03.25.
//

#include "sort_third_stack.h"
#include "integer_stack.h"
#include <stdio.h>
#include <stdlib.h>
#include "validators.h"


int check_increasing(int data, int stack_num)
    {

    while(data <= stack_num)
    {
        data = execute_verification(min_limit, max_limit);
        if (data <=stack_num)
        {
            printf("Введите значение превышающее %d\n", stack_num);
        }

        continue;
    }

    return data;
    }




OBJ* declare_multy_stack(int stack_size, OBJ* top, int stack_number)
{
  if (stack_size < 1)
        {
      printf("Стек пуст...\n");
      return NULL;
        }

    printf("Введите данные %d-го элемента стека-%d:\n", 1, stack_number);
    int regular_data = execute_verification(min_limit, max_limit);
    top = stack_push(top, regular_data);

    for(int i = 1; i < stack_size; i++)
    {

        printf("Введите данные %d-го элемента стека-%d:\n", i + 1, stack_number);


          regular_data = check_increasing(regular_data, top->data);

        top = stack_push(top, regular_data);

    }
    return top;

}




void create_multy_stacks()
{
    printf("Введите размер первого стека:\n");
    int first_stack_size = execute_verification(min_limit, max_limit);
    OBJ* top_one = NULL;
    top_one = declare_multy_stack(first_stack_size, top_one, 1);



    printf("Введите размер второго стека:\n");
    int second_stack_size = execute_verification(min_limit, max_limit);
    OBJ* top_two = NULL;
    top_two = declare_multy_stack(second_stack_size, top_two, 2);

}




void build_third_stack()
    {
      create_multy_stacks();

    }