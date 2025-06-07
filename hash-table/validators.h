//
// Created by jegorix on 24.04.25.
//

#ifndef INC_13LAB_VALIDATORS_H
#define INC_13LAB_VALIDATORS_H
#include <stdio.h>

enum
{
    max_limit = 2147483647,
    min_limit = -2147483647,
    rand_max_limit = 1000000,
    rand_min_limit = -1000000,
};

int execute_verification(int min_limit, int max_limit);
void clearScreen();
#endif //INC_13LAB_VALIDATORS_H
