//
// Created by jegorix on 18.04.25.
//

#include "queue_actions.h"


Queue* create_queue(int queue_size)
{
    Queue* queue = malloc(sizeof(Queue));

    queue->begin = NULL;
    queue->back = NULL;
    queue->max_size = queue_size;
    printf("Очередь успешно создана, ее размер = %d", queue_size);

    return queue;
}




void queue_actions_menu()
{
    printf("Введите максимальный размер очереди\n");
    int queue_size = execute_verification(0, max_limit);
    Queue* queue = create_queue(queue_size);
}
