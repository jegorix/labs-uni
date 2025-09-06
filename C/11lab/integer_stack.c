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

int stack_peek(OBJ* top)
            {
  if (top == NULL)
    {
    return 0;
    }
    return top->data;
            }


 OBJ* declare_stack(int stack_size, OBJ* top, int stack_number)
  {

      for(int i = 0; i < stack_size; i++)
      {
        printf("\n╭───────────────────────────────────╮\n");
          printf("│   Введите данные %d-го элемента    │\n", i + 1);
          printf("│             Стека-%d               │\n", stack_number);
          printf("╰───────────────────────────────────╯\n");
          printf("╰─> ");

        int regular_data = execute_verification(min_limit, max_limit);
        top = stack_push(top, regular_data);

      }
      return top;

  }



OBJ* random_declare_stack(int stack_size, OBJ* top)
      {
  srand(time(NULL));

  for(int i = 0; i < stack_size; i++)
  {

    int regular_data = min + rand() % (max - min + 1);
    top = stack_push(top, regular_data);

  }

  return top;

      }







void stack_print(OBJ* top, int stack_number)
      {

          printf("\n╭───────────────────────────────────╮\n");
          printf("│        Содержимое Стека-%d:        │\n", stack_number);
          printf("╰───────────────────────────────────╯\n");

  if (top == NULL)
    {
      printf("\n╭─────────────────────────╮\n");
        printf("│        Стек пуст        │\n");
        printf("╰─────────────────────────╯\n");
    return;
    }

  OBJ* current = top;
  while(current != NULL)
    {

        printf(
                "┌──────────────┐\n"
                "│ %12d │\n"
                "└──────────────┘\n", current->data
        );
    current = current->next;

    }
    printf("\n");
      }




 void special_stack_output(OBJ* top_1, OBJ* top_2)
          {

            printf("\n╔══════════════════════════════════════╗\n");
              printf("║     Все элементы первого стека,      ║\n");
              printf("║     которые есть во втором стеке:    ║\n");
              printf("╚══════════════════════════════════════╝\n\n");
     OBJ* current_1 = top_1;
     OBJ* current_2 = top_2;

     int flag = 0;

     while(current_1 != NULL)
       {
       while(current_2 != NULL)
         {
       if(current_1->data == current_2->data)
           {
                flag = 1;
               printf(
                       "┌──────────────┐\n"
                       "│ %12d │\n"
                       "└──────────────┘\n", current_1->data
               );
           }
           current_2 = current_2->next;
         }
         current_1 = current_1->next;
         current_2 = top_2;
       }

     if(!flag)
     {
       printf("\n╭───────────────────────────────╮\n");
         printf("│  Равные элементы отсутствуют  │\n");
         printf("╰───────────────────────────────╯\n");
     }

}







void stacks_operations(OBJ* top_1, OBJ* top_2)
    {
  int running = 1;

  while(running)
    {
    printf("\n");

        printf(
              "\n╔════════════════════════════════════════════════════════════╗\n"
                "║                    ВЫБЕРИТЕ ОПЕРАЦИЮ                       ║\n"
                "╠════════════════════════════════════════════════════════════╣\n"
                "║ [1] Содержимое первого стека                               ║\n"
                "║ [2] Содержимое второго стека                               ║\n"
                "║ [3] Содержимое обоих стеков                                ║\n"
                "║ [4] Элементы первого стека, которые есть во втором         ║\n"
                "║ [другое] Выход                                             ║\n"
                "╚════════════════════════════════════════════════════════════╝\n"
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
       special_stack_output(top_1, top_2);
       }break;

    default:
    {
      running = 0;
    }break;

  }

  }

    }











OBJ* init_stack(const char* message, int stack_number)
{

  printf("\n╭───────────────────────────────────╮\n");
    printf("│   %s   │\n", message);
    printf("╰───────────────────────────────────╯\n");
    printf("╰─> ");

  int stack_size = execute_verification(min_limit, max_limit);
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

  char user_input = fgetch();

  switch(user_input)
    {
    case '1':
      top = declare_stack(stack_size, top, stack_number);
      break;

     default:
       top = random_declare_stack(stack_size, top);
       stack_print(top, stack_number);
       break;
    }

   return top;

}



void create_stacks()
{

    OBJ* top_one = init_stack("Введите размер первого стека:", 1);
    OBJ* top_two = init_stack("Введите размер второго стека:", 2);
    stacks_operations(top_one, top_two);

}
