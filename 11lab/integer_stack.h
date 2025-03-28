//
// Created by Macbook on 28.03.25.
//

#ifndef INTEGER_STACK_H
#define INTEGER_STACK_H

typedef struct stack_object
{
    int data;
    struct stack_object* next;
} OBJ;

void create_stacks();
OBJ* declare_stack(int stack_size, OBJ* top, int stack_number);
OBJ* stack_push(OBJ* top, int data);

#endif //INTEGER_STACK_H
