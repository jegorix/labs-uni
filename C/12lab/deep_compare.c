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
        printf("\n╭──────────────────────────────────────────────╮\n");
        printf("│ Очереди имеют разный размер (%3d ≠ %3d).     │\n", size1, size2);
        printf("╰──────────────────────────────────────────────╯\n");
        return 0;
    }

    if(size1 == 0)
    {
        printf("\n╭────────────────────────────╮\n");
        printf("│      Очереди пусты...      │\n");
        printf("╰────────────────────────────╯\n");
        return 1;
    }

    Node* current_1 = queue1->begin;
    Node* current_2 = queue2->begin;

    while(current_1 != NULL && current_2 != NULL)
    {
        if(current_1->value != current_2->value)
        {
            printf("\n╭──────────────────────────────────────────────╮\n");
            printf("│ Очереди различаются: элемент %3d ≠ %3d.      │\n", current_1->value, current_2->value);
            printf("╰──────────────────────────────────────────────╯\n");
            return 0;
        }
        current_1 = current_1->Next;
        current_2 = current_2->Next;
    }
    return 1;
}

void handle_queue(Queue* queue_1, Queue* queue_2, int que_number)
{
    printf("\n╭────────────────────────────────────────────╮\n");
    printf("│      Вы работаете с очередью %3d           │\n", que_number);
    printf("╰────────────────────────────────────────────╯\n");

    int catch;
    int running = 1;
    int res;

    while(running) {
        printf("\n╭────────────────────────────────────────────────────────────╮\n");
        printf("│ Выберите операцию для работы с очередью:                   │\n");
        printf("│ 1 - Вывод очереди на экран                                 │\n");
        printf("│ 2 - Заполнение очереди                                     │\n");
        printf("│ 3 - Добавление элемента в очередь                          │\n");
        printf("│ 4 - Извлечение элемента очереди                            │\n");
        printf("│ 5 - Узнать размер очереди                                  │\n");
        printf("│ 6 - Режим удаления и совпадения                            │\n");
        printf("│ 7 - Стереть очередь                                        │\n");
        printf("│ 8 - Проверить очереди на равенство                         │\n");
        printf("│ 9 - Работать с другой очередью                             │\n");
        printf("│ 10 - Выход в главное меню                                  │\n");
        printf("╰────────────────────────────────────────────────────────────╯\n");
        printf("╰─> ");

        int user_input = execute_verification(1, 10);

        switch (user_input) {
            case 1:
                queue_output(queue_1);
                break;

            case 2:
                queue_fill(queue_1);
                break;

            case 3:
                printf("\n╭──────────────────────────────╮\n");
                printf("│ Введите число для добавления │\n");
                printf("╰──────────────────────────────╯\n");
                printf("╰─> ");
                int data = execute_verification(min_limit, max_limit);
                queue_push(queue_1, data);
                break;

            case 4:
                catch = queue_pop(queue_1);
                if (catch != -1)
                {
                    printf("\n╭───────────────────────────────────────╮\n");
                    printf("│ Первый элемент в очереди: %3d        │\n", catch);
                    printf("╰───────────────────────────────────────╯\n");
                }
                break;

            case 5:
                printf("\n╭────────────────────────────────────╮\n");
                printf("│ Количество элементов очереди: %3d  │\n", get_size(queue_1));
                printf("╰────────────────────────────────────╯\n");
                break;

            case 6:
                clear_queue(queue_1);
                queue_fill(queue_1);
                special_mode(queue_1);
                break;

            case 7:
                clear_queue(queue_1);
                printf("\n╭────────────────────────────────╮\n");
                printf("│    Очередь успешно очищена     │\n");
                printf("╰────────────────────────────────╯\n");
                break;

            case 8:
                res = compare_queues(queue_1, queue_2);
                if(res)
                {
                    printf("\n╭────────────────────────────────╮\n");
                    printf("│      Очереди равны!            │\n");
                    printf("╰────────────────────────────────╯\n");
                    printf("\n╭────────────────────────────╮\n");
                    printf("│        Очередь 1           │\n");
                    printf("╰────────────────────────────╯\n");
                    queue_output(queue_1);
                    printf("\n╭────────────────────────────╮\n");
                    printf("│        Очередь 2           │\n");
                    printf("╰────────────────────────────╯\n");
                    queue_output(queue_2);
                }
                else
                {
                    printf("\n╭────────────────────────────────╮\n");
                    printf("│      Очереди не равны!         │\n");
                    printf("╰────────────────────────────────╯\n");
                    printf("\n╭────────────────────────────╮\n");
                    printf("│        Очередь 1           │\n");
                    printf("╰────────────────────────────╯\n");
                    queue_output(queue_1);
                    printf("\n╭────────────────────────────╮\n");
                    printf("│        Очередь 2           │\n");
                    printf("╰────────────────────────────╯\n");
                    queue_output(queue_2);
                }
                break;

            case 9:
                printf("\n╭────────────────────────────────────────────╮\n");
                printf("│ Переключение на другую очередь (%3d)       │\n", que_number);
                printf("╰────────────────────────────────────────────╯\n");
                return;

            case 10:
                printf("\n╭────────────────────────────╮\n");
                printf("│      Выход из меню...      │\n");
                printf("╰────────────────────────────╯\n");
                running = 0;
                return;
        }
    }
}