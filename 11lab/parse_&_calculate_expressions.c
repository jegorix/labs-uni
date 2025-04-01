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


ObjDouble* stack_pop_double(ObjDouble* top, double* value)
    {
      if (top == NULL) return NULL;

      *value = top->value;
      ObjDouble* temp = top;
      top = top->next;
      free(temp);
      return top;

    }

ObjDouble* stack_push_double(ObjDouble* top, double value)
{
  ObjDouble* temp = malloc(sizeof(ObjDouble));
  temp->value = value;
  temp->next = top;
  return temp;

}





int check_for_errors(char* expression, int* error_position) {
  int balance = 0;
  int expecting_operand = 1; // 1 - ждем операнд или унарный оператор, 0 - ждем оператор
  int pos = 0;

  for (int i = 0; expression[i] != '\0'; i++) {
    if (expression[i] == ' ') continue;
    pos++;

    if (expression[i] == '(') {
      balance++;
      expecting_operand = 1;
    } else if (expression[i] == ')') {
      balance--;
      if (balance < 0) {
        *error_position = pos;
        return 1; // Лишняя закрывающая скобка
      }
      expecting_operand = 0;
    } else if (isdigit(expression[i]) || expression[i] == '.') {
      expecting_operand = 0;
    } else if (expression[i] == '+' || expression[i] == '-' ||
               expression[i] == '*' || expression[i] == '/') {
      if (expecting_operand && (expression[i] == '+' || expression[i] == '-')) {
        // Унарный оператор допустим в начале или после оператора
        continue;
      } else if (!expecting_operand) {
        expecting_operand = 1;
      } else {
        *error_position = pos;
        return 2; // Оператор без операнда
      }
               } else {
                 *error_position = pos;
                 return 3; // Недопустимый символ
               }
  }

  if (balance != 0) {
    *error_position = pos;
    return 1; // Несбалансированные скобки
  }
  if (expecting_operand) {
    *error_position = pos;
    return 2; // Выражение заканчивается оператором
  }
  return 0;
}





StackNode* stack_push_ex(StackNode* top, char* data)
{
  StackNode* temp = malloc(sizeof(StackNode));
  temp->data = strdup(data);
  temp->next = top;
  return temp;
}

StackNode* stack_pop_ex(StackNode* top)
    {
  if (top == NULL)
      {
      return NULL;
      }

      StackNode* temp = top;
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





double evaluate_rpn(char* rpn)
            {
  ObjDouble* stack = NULL;
  char buffer[20];
  int buf_index = 0;

  for(int i = 0; rpn[i] != '\0'; i++)
    {

    if(isdigit(rpn[i]) || rpn[i] == '.')
      {
      buffer[buf_index++] = rpn[i];
      }

    else if (rpn[i] == ' ' && buf_index > 0)
        {
          buffer[buf_index] = '\0';
          stack = stack_push_double(stack, atof(buffer));
          buf_index = 0;
        }

    else if(rpn[i] == '+' || rpn[i] == '-' || rpn[i] == '*' || rpn[i] == '/')
          {
          double a, b, result;
          if(!stack && !stack->next)
            {
            printf("Ошибка! Недостаточно операндов для данной операции\n");
            while(stack){stack = stack_pop_double(stack, &a);}
            return 0;
            }
            stack = stack_pop_double(stack, &b);
            stack = stack_pop_double(stack, &a);

            switch(rpn[i])
            {
              case '+': result = a + b; break;
              case '-': result = a - b; break;
              case '*': result = a * b; break;
              case '/':
                if(b==0)
                  {
                  printf("Ошибка деления на ноль\n");
                  while(stack){stack = stack_pop_double(stack, &a);}
                  return 0;
                  }
                  result = a / b;
                  break;
            }
            stack = stack_push_double(stack, result);
          }
    }
    double final_result;
    if(!stack || stack->next)
      {
      printf("Ошибка: некорректное выражение\n");
      while(stack){stack = stack_pop_double(stack, &final_result);}
      return 0;
      }
      stack = stack_pop_double(stack, &final_result);

      return final_result;


            }





void convert_to_rpn(char* expression, char* rpn_result)
    {
    char buffer[256] = "";
    int buf_index = 0;
    int expecting_operand = 1;
    StackNode* operators = NULL;

    for(int i = 0; expression[i] != '\0'; i++)
      {
          if(expression[i] == ' ') {continue;}

          if (isdigit(expression[i]) || expression[i] == '.')
         {
               buffer[buf_index++] = expression[i];
               expecting_operand = 0;
         }
         else
           {
             if (buf_index > 0)
               {
               buffer[buf_index] = '\0';
               strcat(rpn_result, buffer);
               strcat(rpn_result, " ");
               buf_index = 0;
               }

               if(expression[i] == '(')
               {
                 operators = stack_push_ex(operators, "(");
                 expecting_operand = 1;
               }

               else if (expression[i] == ')')
               {
                 while(operators != NULL && strcmp(operators->data, "(") != 0)
                 {
                   strcat(rpn_result, operators->data);
                   strcat(rpn_result, " ");
                   operators = stack_pop_ex(operators);
                 }

                 if(operators != NULL && strcmp(operators->data, "(") == 0)
                   {
                   operators = stack_pop_ex(operators);
                   }
                 expecting_operand = 0;

               }

               else if (expression[i] == '+' || expression[i] == '-' ||
                        expression[i] == '*' || expression[i] == '/')
                 {
                 if(expecting_operand && (expression[i] == '+' || expression[i] == '-'))
                   {
                   strcat(rpn_result, "0 ");
                   }

                   while(operators != NULL && strcmp(operators->data, "(") != 0
                          && priority(operators->data[0]) >= priority(expression[i]))
                   {
                        strcat(rpn_result, operators->data);
                        strcat(rpn_result, " ");
                        operators = stack_pop_ex(operators);
                   }
                 }

                 char op[2] = {expression[i], '\0'};
                 operators = stack_push_ex(operators, op);
                 expecting_operand = 1;

           }
      }

      if(buf_index > 0)
        {
        buffer[buf_index] = '\0';
        strcat(rpn_result, buffer);
        strcat(rpn_result, " ");
        }

       while(operators != NULL)
         {
           if(strcmp(operators->data, "(") != 0)
           {
             strcat(rpn_result, operators->data);
             strcat(rpn_result, " ");
           }
           operators = stack_pop_ex(operators);
         }

      if(strlen(rpn_result) > 0)
        {
          rpn_result[strlen(rpn_result) - 1] = '\0';
        }


    }






















