//
// Created by jegorix on 19.04.25.
//

#ifndef INC_12LAB_DEQUE_ACTIONS_H
#define INC_12LAB_DEQUE_ACTIONS_H
#include "stdio.h"
#include "validators.h"
#include "stdlib.h"
#include <time.h>
#include <string.h>

typedef struct
{
    int value;
    struct deNode* Next;
    struct deNode* Prev;
}deNode;

typedef struct
{
    deNode* begin;
    deNode* back;
    int max_size;
}Deque;

void deque_actions_menu();
Deque* create_deque(int deque_size);
void deque_output(Deque* deque);
int isEmpty(Deque* deque);
int get_size_deq(Deque* deque);
void push_front(Deque* deque, int data);
void push_back(Deque* deque, int data);
void deque_push_menu(Deque* deque, int value);
void deque_fill(Deque* deque);
void deque_pop_menu(Deque* deque);
int pop_front(Deque* deque);
int pop_back(Deque* deque);
void clear_deque(Deque* deque);

#endif //INC_12LAB_DEQUE_ACTIONS_H
