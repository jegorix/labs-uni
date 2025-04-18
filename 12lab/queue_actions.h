//
// Created by jegorix on 18.04.25.
//

#ifndef INC_12LAB_QUEUE_ACTIONS_H
#define INC_12LAB_QUEUE_ACTIONS_H
#include "stdio.h"
#include "validators.h"
#include "stdlib.h"
#include <time.h>
#include <string.h>

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

void queue_push(Queue* queue, int value);
Queue* create_queue(int queue_size);
void queue_output(Queue *queue);
void queue_actions_menu();
int get_size(Queue* queue);
void queue_fill(Queue* queue);
int queue_pop(Queue* queue);

#endif //INC_12LAB_QUEUE_ACTIONS_H
