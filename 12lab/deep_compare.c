//
// Created by jegorix on 19.04.25.
//

#include "deep_compare.h"


int compare_queues(Queue* queue1, Queue* queue2)
{
    int size1 = get_size(queue1);
    int size2 = get_size(queue2);

    if(size1 != size2)
    {
        printf("Очереди имеют разный размер (%d ≠ %d).\n", size1, size2);
        return 0;
    }

    if(size1 == 0)
    {
        printf("Очереди пусты...\n");
        return 1;
    }

    Node* current_1 = queue1->begin;
    Node* current_2 = queue2->begin;

    while(current_1 != NULL && current_2 != NULL)
    {
        if(current_1->value != current_2->value)
        {
            printf("Очереди различаются: элемент %d ≠ %d.\n", current_1->value, current_2->value);
            return 0;
        }
        current_1 = current_1->Next;
        current_2 = current_2->Next;
    }
    return 1;
}





void handle_queue(Queue* queue_1, Queue* queue_2, int que_number)
{
    printf("\n >> Вы работаете с очередью %d << \n", que_number);

    int catch;
    int running = 1;
    int res;

    while(running) {

        printf("\nВыберите операцию для работы с очередью:\n"
               "1 - Вывод очереди на экран\n"
               "2 - Заполнение очереди\n"
               "3 - Добавление элемента в очередь\n"
               "4 - Извлечение элемента очереди\n"
               "5 - Узнать размер очереди\n"
               "6 - Режим удаления и совпадения\n"
               "7 - Стереть очередь\n"
               "\n>> 8 - Проверить очереди на равенство <<\n"
               "\n9 - Работать с другой очередью\n"
               "10 - Выход в главное меню\n");

        int user_input = execute_verification(1, 10);

        switch (user_input) {
            case 1:
                queue_output(queue_1);
                break;

            case 2:
                queue_fill(queue_1);
                break;

            case 3:
                printf("\nВведите число для добавления:\n");
                printf(">> ");
                int data = execute_verification(min_limit, max_limit);
                queue_push(queue_1, data);
                break;

            case 4:
                catch = queue_pop(queue_1);
                printf("\nПервый элемент в очереди %d\n", catch);
                break;


            case 5:
                printf("Количество элементов очереди: %d\n", get_size(queue_1));
                break;

            case 6:
                clear_queue(queue_1);
                queue_fill(queue_1);
                special_mode(queue_1);


            case 7:
                clear_queue(queue_1);
                printf("\nОчередь успешно очищена\n");
                break;

            case 8:
                res = compare_queues(queue_1, queue_2);
                if(res)
                {
                    printf("\nОчереди равны!\n");
                    printf("\nОчередь 1\n");
                    queue_output(queue_1);
                    printf("\nОчередь 2\n");
                    queue_output(queue_2);
                }
                else
                {
                    printf("\nОчереди не равны!\n");
                    printf("\nОчередь 1\n");
                    queue_output(queue_1);
                    printf("\nОчередь 2\n");
                    queue_output(queue_2);
                }
                break;

            case 9:
                printf("Работа с другой очередью %d\n", que_number);
                return;



            case 10:
                printf("Выход...\n");
                running = 0;
                return;

        }

    }
}