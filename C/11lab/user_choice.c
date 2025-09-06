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


      printf(
            "\n╔═══════════════════════════════════════════════════════════╗\n"
              "║                      ВЫБОР ДЕЙСТВИЯ                       ║\n"
              "╠═══════════════════════════════════════════════════════════╣\n"
              "║  [1] Задача №1 — элементы из первого стека во втором      ║\n"
              "║  [2] Задача №2 — создать третий стек по возрастанию       ║\n"
              "║  [3] Задача №3 — работа со стеком в текстовом файле       ║\n"
              "║  [q] Выход из программы                                   ║\n"
              "╚═══════════════════════════════════════════════════════════╝\n"
      );

      printf(
              "\n╭───────────────────────────────────╮\n"
              "│        Введите команду:           │\n"
              "╰───────────────────────────────────╯\n"
              "╰─> "
      );


      char user_input = fgetch();

      switch(user_input)
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

          case 'q':
          {
              exit = 1;
          }break;


        default:
          {
              printf("\n╔══════════════════════════════════════╗\n");
              printf("║        Неизвестная команда!          ║\n");
              printf("║     Пожалуйста, попробуйте ещё раз.  ║\n");
              printf("╚══════════════════════════════════════╝\n\n");
          }

      }


}
    }
