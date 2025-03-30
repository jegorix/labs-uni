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


OBJ* stack_push_double(OBJ* top, double data)
{
  OBJ* temp = malloc(sizeof(OBJ));
  temp->data = data;
  temp->next = top;
  return temp;
}





void convert_to_rpn(char* expression)
    {
  char* token = strtok(expression, " ");
  while(token != NULL)
      {
        char* endptr;
        double number = strtod(token, &endptr);
        if (*endptr == '\0')
          {
          printf("%s\n", token);
          }

        token = strtok(NULL, " ");

      }
    }


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

    char* endptr;
    double number = strtod(token, &endptr);

    if (*endptr == '\0')
      {
      printf("Добавляю в стек: %lf\n", number);
      top = stack_push_double(top, number);
      }

     else if (is_operator(token[0]))
        {
          if(top == NULL || top->next == NULL)
            {
            printf("Недостаточное количество операндов для операции '%c'\n", token[0]);
            return;
            }

            double b = top->data;
            top = stack_pop(top);
            double a = top->data;
            top = stack_pop(top);
            double result;

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

        top = stack_push_double(top, result);
        printf("%.2lf %c %.2lf = %.2lf\n", a, token[0] , b, result);

        }

      token = strtok(NULL, " ");

    }

    }
