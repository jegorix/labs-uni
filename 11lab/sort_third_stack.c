//
// Created by Macbook on 28.03.25.
//

#include "sort_third_stack.h"
#include "integer_stack.h"
#include <stdio.h>
#include <stdlib.h>
#include "validators.h"


void output_reverse_stack(OBJ* top)
    {
      if (top == NULL)
        {
        return;
        }

        output_reverse_stack(top->next);
        printf("%d\n", top->data);

    }




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


OBJ* make_third_stack(int stack_size_1, int stack_size_2, OBJ* top_1, OBJ* top_2)
    {

          OBJ* current_1 = top_1;
          OBJ* current_2 = top_2;
          OBJ* third_stack = NULL;

          while(current_1 != NULL && current_2 != NULL)
            {
            if (current_1->data < current_2->data)
              {
              third_stack = stack_push(third_stack, current_2->data);
              current_2 = current_2->next;
              }
              else
                {
                third_stack = stack_push(third_stack, current_1->data);
                current_1 = current_1->next;
                }

            }

            while(current_1 != NULL)
              {
              third_stack = stack_push(third_stack, current_1->data);
              current_1 = current_1->next;
              }

            while(current_2 != NULL)
            {
                third_stack = stack_push(third_stack, current_2->data);
                current_2 = current_2->next;
            }


        return third_stack;
    }



 void user_action(OBJ* top_1, OBJ* top_2, OBJ* top_3)
        {
        printf("Выберите действие:\n");
    int running = 1;

    while(running)
    {
        printf("\n");
        char user_input[50];
        printf("Выберите операцию:\n");
        printf("Содержимое первого стека: - 1\n");
        printf("Содержимое второго стека: - 2\n");
        printf("Содержимое обоих стеков: - 3\n");
        printf("Третий стек отсортирванный по возрастанию: - 4\n");
        printf("Третий стек отсортирванный по убыванию: - 5\n");
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
                stack_print(top_3, 3);
            }break;

            case '5':
            {
                if (top_3 == NULL)
                {
                    printf("Стек пуст...\n");
                    return;
                }
              printf("Содержимое Стека № %d\n", 3);
              output_reverse_stack(top_3);
            }break;

            default:
            {
                running = 0;
            }break;

        }

    }

        }



void create_multy_stacks()
{
    printf("Введите размер первого стека:\n");
    int first_stack_size = execute_verification(min_limit, max_limit);
    OBJ* top_one = NULL;
    top_one = declare_multy_stack(first_stack_size, top_one, 1);
    stack_print(top_one, 1);



    printf("Введите размер второго стека:\n");
    int second_stack_size = execute_verification(min_limit, max_limit);
    OBJ* top_two = NULL;
    top_two = declare_multy_stack(second_stack_size, top_two, 2);
    stack_print(top_two, 2);


    OBJ* third_stack = make_third_stack(first_stack_size, second_stack_size, top_one, top_two);


    user_action(top_one, top_two, third_stack);

}




void build_third_stack()
    {
      create_multy_stacks();

    }