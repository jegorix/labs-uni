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
      printf("число = %d добавлено в стек\n", number);
      }

      token = strtok(NULL, " ");
    }

    }
