//
// Created by Macbook on 28.03.25.
//

#include "sort_third_stack.h"
#include "integer_stack.h"
#include <stdio.h>
#include <stdlib.h>
#include "validators.h"






void make_reverse_stack(OBJ* top)
    {
        if (top == NULL) return;

        make_reverse_stack(top->next);

        printf(
                "┌──────────────┐\n"
                "│ %12d │\n"
                "└──────────────┘\n", top->data
        );

    }



void output_reverse_stack(OBJ* top, int number)
{
    if (top == NULL)
    {
        printf("\n╭─────────────────────────╮\n");
        printf("│        Стек пуст        │\n");
        printf("╰─────────────────────────╯\n");
        return;
    }

    printf("\n╭───────────────────────────────────╮\n");
    printf("│        Содержимое Стека-%d:        │\n", number);
    printf("╰───────────────────────────────────╯\n");

    make_reverse_stack(top);

}





int check_increasing(int prev_data, int stack_num)
    {

    int data = prev_data;

    while(data <= stack_num)
    {
          printf("\n╭───────────────────────────────────╮\n");
            printf("│ Введите значение превышающее %3d: │\n", stack_num);
            printf("╰───────────────────────────────────╯\n");
            printf("╰─> ");
            data = execute_verification(min_limit, max_limit);
    }

    return data;
    }




OBJ* declare_multy_stack(int stack_size, OBJ* top, int stack_number)
{
  if (stack_size < 1)
        {
            printf("\n╭─────────────────────────╮\n");
            printf("│        Стек пуст        │\n");
            printf("╰─────────────────────────╯\n");
      return NULL;
        }

    printf("\n╭───────────────────────────────────╮\n");
    printf("│   Введите данные %d-го элемента    │\n", 1);
    printf("│             Стека-%d               │\n", stack_number);
    printf("╰───────────────────────────────────╯\n");
    printf("╰─> ");
    int regular_data = execute_verification(min_limit, max_limit);
    top = stack_push(top, regular_data);

    for(int i = 1; i < stack_size; i++)
    {

        printf("\n╭───────────────────────────────────╮\n");
        printf("│   Введите данные %d-го элемента    │\n", i + 1);
        printf("│             Стека-%d               │\n", stack_number);
        printf("╰───────────────────────────────────╯\n");
        printf("╰─> ");


          regular_data = check_increasing(regular_data, top->data);

        top = stack_push(top, regular_data);

    }
    return top;

}







OBJ* random_declare_multy_stack(int stack_size, OBJ* top)
{

    if (stack_size < 1)
    {
        printf("\n╭─────────────────────────╮\n");
        printf("│        Стек пуст        │\n");
        printf("╰─────────────────────────╯\n");
        return NULL;
    }


    int regular_data =  -100 + rand() % (201);
    top = stack_push(top, regular_data);

    for(int i = 1; i < stack_size; i++)
    {
         int delta = 1 + rand() % 100;
         regular_data += delta;

        top = stack_push(top, regular_data);

    }
    return top;

}









OBJ* make_third_stack( OBJ* top_1, OBJ* top_2)
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
    int running = 1;

    while(running)
    {
        printf("\n");



        printf(
                "\n╔══════════════════════════════════════════════════════╗\n"
                "║                  ВЫБЕРИТЕ ОПЕРАЦИЮ                   ║\n"
                "╠══════════════════════════════════════════════════════╣\n"
                "║ [1] Содержимое первого стека                         ║\n"
                "║ [2] Содержимое второго стека                         ║\n"
                "║ [3] Содержимое обоих стеков                          ║\n"
                "║ [4] Третий стек (по возрастанию)                     ║\n"
                "║ [5] Третий стек (по убыванию)                        ║\n"
                "║ [другая клавиша] Выход                               ║\n"
                "╚══════════════════════════════════════════════════════╝\n"
        );

        printf("\n╭───────────────────────────────────╮\n");
        printf("│        Введите команду:           │\n");
        printf("╰───────────────────────────────────╯\n");
        printf("╰─> ");

        char user_input = fgetch();

        switch(user_input)
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
              output_reverse_stack(top_3, 3);
            }break;

            default:
            {
                running = 0;
            }break;

        }

    }

        }



int get_stack_size(OBJ* top)
{
    OBJ* current = top;
    int size = 0;
    while(current != NULL)
    {
        size++;
        current = current->next;
    }

    return size;
}




OBJ* init_spec_stack(int number)
{

  printf("\n╭───────────────────────────────────╮\n");
    printf("│   Введите размер стека №%d:        │\n", number);
    printf("╰───────────────────────────────────╯\n");
    printf("╰─> ");


    int stack_size = execute_verification(0, max_limit);
    OBJ* top = NULL;


    printf(
            "\n╔══════════════════════════════════════════════╗\n"
            "║            ВЫБЕРИТЕ ТИП ЗАПОЛНЕНИЯ           ║\n"
            "╠══════════════════════════════════════════════╣\n"
            "║ [1] Ввести элементы вручную                  ║\n"
            "║ [другое] Случайное заполнение                ║\n"
            "╚══════════════════════════════════════════════╝\n"
    );


    printf("\n╭───────────────────────────────────╮\n");
    printf("│        Введите команду:           │\n");
    printf("╰───────────────────────────────────╯\n");
    printf("╰─> ");

    char user_choice = fgetch();

    switch(user_choice)
    {
        case '1':
            top = declare_multy_stack(stack_size, top, number);
        break;

        default:
            top = random_declare_multy_stack(stack_size, top);
        break;


    }

    stack_print(top, number);

    return top;

}





void create_multy_stacks()
{
    srand(time(NULL));

    OBJ* top_one = init_spec_stack(1);
    OBJ* top_two = init_spec_stack(2);

    OBJ* third_stack = make_third_stack(top_one, top_two);

    user_action(top_one, top_two, third_stack);

}





void build_third_stack()
    {
      create_multy_stacks();

    }