//
// Created by Macbook on 28.03.25.
//

#include "validators.h"


int execute_verification(int min_limit, int max_limit)
{
  char input[100];
  int number;
  char symbol;

  while(1)
  {
    if(fgets(input, sizeof(input), stdin) == NULL)
    {
      printf("Ошибка ввода! Попробуйте еще раз!\n");
      continue;
    }

    if (sscanf(input, "%d %c", &number, &symbol) != 1)
    {
      printf("Ошибка ввода! Введите целое число:\n");
      continue;
    }

    if (number > max_limit || number < min_limit)
    {
      printf("Ошибка ввода! Введите число из диапазона [%d, %d]:\n", min_limit, max_limit);
      continue;
    }

    return number;

  }

}



float execute_verification_float(float min_limit, float max_limit)
{
  char input[100];
  float number;
  char symbol;

  while(1)
  {
    if(fgets(input, sizeof(input), stdin) == NULL)
    {
      printf("Ошибка ввода! Попробуйте еще раз!\n");
      continue;
    }

    if (sscanf(input, "%f %c", &number, &symbol) != 1)
    {
      printf("Ошибка ввода! Введите число с плавающей запятой:\n");
      continue;
    }

    if (number > max_limit || number < min_limit)
    {
      printf("Ошибка ввода! Введите число из диапазона [%.2f, %.2f]:\n", min_limit, max_limit);
      continue;
    }

    return number;

  }

}
