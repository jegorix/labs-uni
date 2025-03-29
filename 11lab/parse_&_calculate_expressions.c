//
// Created by Macbook on 29.03.25.
//

#include "parse_&_calculate_expressions.h"
#include "arithmetic_expressions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "validators.h"
#include "integer_stack.h"
#include "ctype.h"

int is_operator(char c)
    {
  return (c == '+' || c == '-' || c == '*' || c == '/' );
    }

void parse_expressions(char* expression)
    {
  char* token = strtok(expression, " ");
   OBJ* top = NULL;

  while(token != NULL)
    {

    if(isdigit(token[0]) || (token[0] == '-' && isdigit(token[1])))
      {
      int number = atoi(token);
      top = stack_push(top, number);

      }

     else if (is_operator(token[0]))
        {
          if(top == NULL || top->next == NULL)
            {
            printf("Недостаточное количество операндов для операции '%c'\n", token[0]);
            return;
            }

            int b = top->data;
            top = stack_pop(top);
            int a = top->data;
            top = stack_pop(top);
            int result;

            switch (token[0])
            {
              case '+': result = a + b; break;
              case '-': result = a - b; break;
              case '*': result = a * b; break;
              case '/':
                if (b == 0)
                  {
                   printf("Деление на 0 выполнить невозможно\n");
                   return;
                  }
                  result = a / b;
                  break;
            }

        top = stack_push(top, result);
        printf("%d %c %d = %d\n", a, token[0] , b, result);

        }

      token = strtok(NULL, " ");

    }

    }
