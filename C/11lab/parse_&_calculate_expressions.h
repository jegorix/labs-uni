//
// Created by Macbook on 29.03.25.
//

#ifndef PARSE___CALCULATE_EXPRESSIONS_H
#define PARSE___CALCULATE_EXPRESSIONS_H

typedef struct StackNode
    {
  char* data;
  struct StackNode* next;
    } StackNode;


typedef struct ObjDouble
        {
  double value;
  struct ObjDouble* next;
        } ObjDouble;

void parse_expressions(char* expression);
int is_operator(char c);
void convert_to_rpn(char* expression, char* rpn_result);
int check_for_errors(char* expression, int* error_position);
double evaluate_rpn(char* rpn);
#endif //PARSE___CALCULATE_EXPRESSIONS_H
