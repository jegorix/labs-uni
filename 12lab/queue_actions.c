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


void queue_output(Queue* queue)
{
    Node* current = queue->begin;
    printf("Очередь:\n");

    if(current == NULL)
    {
        printf("Очередь пуста...\n");
        return;
    }

    while (current != NULL)
    {
        printf("%d\n", current->value);
        current = current->Next;
    }

}


int get_size(Queue* queue)
{
    int q_size = 0;
    Node* current = queue->begin;
    while(current != NULL)
    {
        q_size++;
        current = current->Next;
    }

    return q_size;
}


void queue_push(Queue* queue, int value)
{
    int current_size = get_size(queue);

    if(current_size >= queue->max_size)
    {
        printf("Очередь переполнена! Нельзя добавить элемент %d (максимальный размер: %d).\n", value, queue->max_size);
    }

    Node* new_node = malloc(sizeof(new_node));

    new_node->value = value;
    new_node->Next = NULL;

    if(queue->back == NULL)
    {
        queue->back = new_node;
        queue->begin = new_node;
    }

    else
    {
       queue->back->Next = new_node;
       queue->back = new_node;
    }

}





void queue_actions_menu()
{
    printf("Введите максимальный размер очереди\n");
    int queue_size = execute_verification(0, max_limit);
    Queue* queue = create_queue(queue_size);

    while(1) {

        printf("Выберите операцию для работы с очередью:\n"
               "1 - Вывод очереди на экран\n"
               "2 - Заполнение очереди\n"
               "3 - Добавление элемента в очередь\n"
               "4 - Извлечение элемента очереди\n"
               "5 - Узнать размер очереди\n"
               "6 - Режим удаления и совпадения\n"
               "7 - Выход\n");

        int user_input = execute_verification(1, 7);

        switch (user_input) {
            case 1:
                queue_output(queue);
                break;

            case 2:
//            queue_fill(queue);
                break;

            case 3:
                printf("Введите число для добавления:\n");
                int data = execute_verification(min_limit, max_limit);
                queue_push(queue, data);
                break;

            case 5:
                printf("Количество элементов очереди: %d\n", get_size(queue));
                break;

            case 7:
                printf("Выход...\n");
                exit(1);
                break;

        }

    }


}
