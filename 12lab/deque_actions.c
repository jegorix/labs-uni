//
// Created by jegorix on 19.04.25.
//
//Создать дек для целых чисел. Максимальный размер дека вводится с экрана. Создать
//функции для ввода и вывода элементов дека. При каждом вводе числа слева удаляется элемент, и если
//он не совпадает с введенным числом, то введенное число добавляется справа.
//



#include "deque_actions.h"


Deque* create_deque(int deque_size)
{
    Deque* deque = malloc(sizeof(Deque));
    deque->begin = NULL;
    deque->back = NULL;
    deque->max_size = deque_size;
    printf("Дек был успешно создан, его размер = %d", deque->max_size);
    return deque;
}

int isEmpty(Deque* deque)
{
    return deque->begin == NULL;
}

int get_size_deq(Deque* deque)
{
    deNode* current = deque->begin;
    int size = 0;
    while(current != NULL)
    {
        size++;
        current = current->Next;
    }
    return size;
}



void deque_output(Deque* deque)
{
    if(isEmpty(deque))
    {
        printf("\nДек пуст...\n");
        return;
    }

    printf("\nВ каком формате вывести дек?\n"
           "В прямой последовательности - любая клавиша\n"
           "В обратной последовательности - 1\n");

    char user_input[50];
    deNode* current_1 = deque->back;
    deNode* current_2 = deque->begin;
    fgets(user_input, 50, stdin);

    switch (user_input[0]) {
        case '1':
            printf("\nСодержимое дека в обратном порядке:\n");
            while(current_1 != NULL)
            {
                printf("%d ", current_1->value);
                current_1 = current_1->Prev;
            }
            printf("\n");
            break;

        default:
            printf("\nСодержимое дека в прямом порядке:\n");
            while(current_2 != NULL)
            {
                printf("%d ", current_2->value);
                current_2 = current_2->Next;
            }
            printf("\n");

    }

}


void push_front(Deque* deque, int data)
{
    int deSize = get_size_deq(deque);
    if(deSize >= deque->max_size)
    {
        printf("Дек переполнен! Нельзя добавить элемент %d (максимальный размер: %d).\n", data, deque->max_size);
        return;
    }

    deNode* newNode = malloc(sizeof(deNode));
    newNode->Next = NULL;
    newNode->Prev = NULL;
    newNode->value = data;

    if(deque->begin == NULL)
    {
        deque->begin = newNode;
        deque->back = newNode;
    }
    else
    {
        newNode->Next = deque->begin;
        deque->begin->Prev = newNode;
        deque->begin = newNode;
    }

}



void push_back(Deque* deque, int data)
{
    int deSize = get_size_deq(deque);
    if(deSize >= deque->max_size)
    {
        printf("Дек переполнен! Нельзя добавить элемент %d (максимальный размер: %d).\n", data, deque->max_size);
        return;
    }

    deNode* newNode = malloc(sizeof(deNode));
    newNode->Next = NULL;
    newNode->Prev = NULL;
    newNode->value = data;

    if(deque->back == NULL)
    {
        deque->begin = newNode;
        deque->back = newNode;
    }
    else
    {
        newNode->Prev = deque->back;
        deque->back->Next = newNode;
        deque->back = newNode;
    }

}



void deque_push_menu(Deque* deque, int value)
{
    printf("\nВыберите место добавления элемента в дек\n"
           "В начало - 1\n"
           "В конец -  любая другая клавиша\n");

    char user_input[50];

    fgets(user_input, 50, stdin);

    switch (user_input[0]) {
        case '1':
            push_front(deque, value);
            printf("\nЭлемент %d успешно добавлен в начало дека\n", value);
            break;

        default:
            push_back(deque, value);
            printf("\nЭлемент %d успешно добавлен в конец дека\n", value);


    }

}


void deque_fill(Deque* deque)
{
    int current_size = get_size_deq(deque);
    if (current_size >= deque->max_size)
    {
        printf("\nНевозможно выполнить операцию заполнение дека,\n"
               "так как он уже заполнен\n");
        return;
    }

    printf("Заполнение в ручную - 1\n");
    printf("Случайными значениями - любая другая клавиша\n");
    char user_input[50];
    fgets(user_input, 50, stdin);

    switch (user_input[0]) {

        case '1':
        {
            for (int i = 0; i < deque->max_size - get_size_deq(deque); i++) {
                printf("Введите число для добавления:\n");
                int data = execute_verification(min_limit, max_limit);
                push_back(deque, data);
            }
            printf("\nДек был успешно заполнен!\n");
        }break;

        default:
        {
            for (int i = 0; i < deque->max_size - get_size_deq(deque); i++) {
                int data = rand_min_limit + rand() % (rand_max_limit - rand_min_limit + 1);
                push_back(deque, data);
            }
            printf("\nДек был успешно заполнен!\n");
        }break;


    }


}




void deque_actions_menu()
{
    printf("Введите максимальный размер дека\n");
    int deque_size = execute_verification(0, max_limit);
    Deque* deque = create_deque(deque_size);
    int catch;
    int running = 1;

    while(running) {

        printf("\nВыберите операцию для работы с деком:\n"
               "1 - Вывод дека на экран\n"
               "2 - Заполнение дека\n"
               "3 - Добавление элемента в дек\n"
               "4 - Извлечение элемента из дека\n"
               "5 - Узнать размер дека\n"
               "6 - Режим удаления и совпадения\n"
               "7 - Стереть дек\n"
               "8 - Выход\n");

        int user_input = execute_verification(1, 8);

        switch (user_input) {
            case 1:
                deque_output(deque);
                break;

            case 2:
                deque_fill(deque);
                break;

            case 3:
                if(get_size_deq(deque) >= deque->max_size)
                {
                    printf("Дек переполнен! Нельзя добавить элемент (максимальный размер: %d).\n",deque->max_size);
                    continue;
                }
                printf("Введите число для добавления:\n");
                int data = execute_verification(min_limit, max_limit);
                deque_push_menu(deque, data);
                break;
//
//            case 4:
//                catch = queue_pop(queue);
//                if(catch == -1)
//                {
//                    continue;
//                }
//                printf("\nПервый элемент в очереди %d\n", catch);
//                break;
//
//
            case 5:
                printf("Количество элементов очереди: %d\n", get_size_deq(deque));
                break;
//
//            case 6:
//                clear_queue(queue);
//                queue_fill(queue);
//                special_mode(queue);
//
//
//            case 7:
//                clear_queue(queue);
//                printf("\nОчередь успешно очищена\n");
//                break;
//
//            case 8:
//                printf("Выход...\n");
//                running = 0;
//                continue;

        }

    }


}
