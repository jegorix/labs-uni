//
// Created by Macbook on 28.03.25.
//

#ifndef VALIDATORS_H
#define VALIDATORS_H
#include <stdio.h>

enum
{
    max_limit = 2147483647,
    min_limit = -2147483647,
    rand_max_limit = 1000000,
    rand_min_limit = -1000000,
  };

int execute_verirfication(int min_limit, int max_limit);
float execute_verirfication_float(float min_limit, float max_limit);


#endif //VALIDATORS_H
