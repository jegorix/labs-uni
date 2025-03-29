//
// Created by Macbook on 29.03.25.
//

#include "parse_&_calculate_expressions.h"
#include "arithmetic_expressions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "validators.h"

int is_operator(char c)
    {
  return (c == '+' || c == '-' || c == '*' || c == '/' );
    }

void parse_expressions(char* expression)
    {
  char* token = strtok(expression, " ");
  while(token != NULL)
    {
    if (is_operator(token[0]))
          {
          printf("Оператор - %s\n", token);
          }

     else
        {
           printf("Операнд - %s\n", token);
        }

       token = strtok(NULL, " ");
    }

    }
