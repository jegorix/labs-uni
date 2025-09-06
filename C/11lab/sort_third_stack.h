//
// Created by Macbook on 28.03.25.
//

#ifndef SORT_THIRD_STACK_H
#define SORT_THIRD_STACK_H

#include "integer_stack.h"

void create_multy_stacks();
int get_stack_size(OBJ* top);
OBJ* init_spec_stack(int number);
OBJ* declare_multy_stack(int stack_size, OBJ* top, int stack_number);
void build_third_stack();
int check_increasing(int data, int stack_num);
void user_action(OBJ* top_1, OBJ* top_2, OBJ* top_3);
OBJ* make_third_stack( OBJ* top_1, OBJ* top_2);
void make_reverse_stack(OBJ* top);
void output_reverse_stack(OBJ* top, int number);

#endif //SORT_THIRD_STACK_H
