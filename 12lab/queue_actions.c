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






void queue_actions_menu()
{
    printf("Введите максимальный размер очереди\n");
    int queue_size = execute_verification(0, max_limit);
    Queue* queue = create_queue(queue_size);

    printf("Выберите операцию для работы с очередью:\n"
           "1 - Вывод очереди на экран\n"
           "2 - Заполнение очереди\n"
           "3 - Добавление элемента в очередь\n"
           "4 - Извлечение элемента очереди\n"
           "5 - Узнать размер очереди\n"
           "6 - Режим удаления и совпадения\n");

    int user_input = execute_verification(1,6);

    switch (user_input)
    {
        case 1:
            queue_output(queue);

    }




}
