//
// Created by Macbook on 28.03.25.
//

#ifndef SORT_THIRD_STACK_H
#define SORT_THIRD_STACK_H

#include "integer_stack.h"

void create_multy_stacks();
OBJ* declare_multy_stack(int stack_size, OBJ* top, int stack_number);
void build_third_stack();
int check_increasing(int data, int stack_num);
void user_action(OBJ* top_1, OBJ* top_2, OBJ* top_3);
OBJ* make_third_stack(int stack_size_1, int stack_size_2, OBJ* top_1, OBJ* top_2);

#endif //SORT_THIRD_STACK_H
