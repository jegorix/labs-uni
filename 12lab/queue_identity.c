//
// Created by jegorix on 19.04.25.
//
//Проверьте на равенство две очереди. Решение в программе оформляйте через подпрограммы.
#include "queue_identity.h"


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
        current_1->Next;
        current_2->Next;
    }
 return 1;
}





void handle_queue(Queue* queue_1, Queue* queue_2, int que_number)
{
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
               "6 - Проверка очередей на равенство\n"
               "7 - Стереть очередь\n"
               "\n>> 8 - Проверить очереди на равенство <<\n"
               "\n9 - Работать с другой очередью\n"
               "10 - Выход\n");

        int user_input = execute_verification(1, 10);

        switch (user_input) {
            case 1:
                queue_output(queue_1);
                break;

            case 2:
                queue_fill(queue_1);
                break;

            case 3:
                printf("Введите число для добавления:\n");
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
                   printf("Очереди равны!\n");
               }
               else
               {
                   printf("Очереди не равны!\n");
               }
                break;

            case 9:
                printf("Работа с другой очередью %d\n", que_number);
                return;



            case 10:
                printf("Выход...\n");
                running = 0;
                exit(1);

        }

    }
}




void queue_identity_menu() {
    printf("\nВведите максимальный размер очереди №1:\n");
    int queue_size_1 = execute_verification(0, max_limit);
    Queue *queue_1 = create_queue(queue_size_1);

    printf("\nВведите максимальный размер очереди №2:\n");
    int queue_size_2 = execute_verification(0, max_limit);
    Queue *queue_2 = create_queue(queue_size_2);

    int running = 1;

    while (running) {
        printf("\nС какой очередью вы желаете работать?\n"
               "Очередь №1 - 1\n"
               "Очередь №2 - 2\n"
               "Выход - 3\n");

        int user_choice = execute_verification(1, 3);

        switch (user_choice) {
            case 1:
                handle_queue(queue_1, queue_2, user_choice);
                break;

            case 2:
                handle_queue(queue_2, queue_1, user_choice);
                break;

            case 3:
                running = 0;
                break;

        }
    }
}