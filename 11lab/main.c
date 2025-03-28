//
// Created by Macbook on 28.03.25.
//
#include <stdio.h>
#include "validators.h"
#include "integer_stack.h"

int main()
 {
  int number;
  printf("Enter a number:\n");
  scanf("%d", &number);
  int result = positivenum(number);
 printf("%d\n", result);

 integer_stack_init();



  return 0;
 }