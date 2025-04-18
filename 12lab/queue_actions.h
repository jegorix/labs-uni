//
// Created by jegorix on 18.04.25.
//

#ifndef INC_12LAB_QUEUE_ACTIONS_H
#define INC_12LAB_QUEUE_ACTIONS_H
#include "stdio.h"
#include "validators.h"
#include "stdlib.h"

typedef struct
{
    int value;
    struct Node* Next;
}Node;

typedef struct
{
    Node* begin;
    Node* back;
    int max_size;
}Queue;


Queue* create_queue(int queue_size);
void queue_output(Queue *queue);
void queue_actions_menu();

#endif //INC_12LAB_QUEUE_ACTIONS_H
