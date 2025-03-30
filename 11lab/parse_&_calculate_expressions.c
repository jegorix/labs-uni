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






int check_for_errors(char* expression, int* error_position)
    {
  int pos = 0;
  int balance = 0;

  for(int i = 0; expression[i] != '\0'; i++)
    {
    pos++;
    if(expression[i] == '(')
      {
          balance++;
      }

      else if(expression[i] == ')')
        {
          balance--;
          if (balance < 0)
            {
                *error_position = pos;
                return 1;
            }
        }

        else if ((expression[i] < '0' || expression[i] > '9') &&
               expression[i] != '-' && expression[i] != '+' &&
               expression[i] != '*' && expression[i] != '/' &&
                expression[i] != '.' && expression[i] != ' ')
          {
          *error_position = pos;
          return 2;
          }

    }
    if (balance == 0)
      {
      *error_position = pos;
      return 3;
      }
      return 0;
    }






StractNode* stack_push_ex(StractNode* top, char* data)
{
  StractNode* temp = malloc(sizeof(StractNode));
  temp->data = strdup(data);
  temp->next = top;
  return temp;
}

StractNode* stack_pop_ex(StractNode* top)
    {
  if (top == NULL)
      {
      return NULL;
      }

      StractNode* temp = top;
      top = top->next;
      free(temp->data);
      free(temp);

      return top;

    }


 int priority(char operator)
        {
   if (operator == '+' || operator == '-')
     {return 1;}
   else if (operator == '*' || operator == '/')
     {return 2;}
   return 0;
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
