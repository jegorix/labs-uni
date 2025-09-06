//
// Created by jegorix on 19.04.25.
//

#include "deque_actions.h"

Deque* create_deque(int deque_size)
{
    Deque* deque = malloc(sizeof(Deque));
    deque->begin = NULL;
    deque->back = NULL;
    deque->max_size = deque_size;

    printf("\n╭────────────────────────────────────────────╮\n");
    printf("│  Дек успешно создан, его размер = %3d      │\n", deque->max_size);
    printf("╰────────────────────────────────────────────╯\n");
    printf("╰─> ");
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


void deq_base_output(Deque* deque)
{
    deNode* current_2 = deque->begin;
    printf("\n╭────────────────────────────────────╮\n");
    printf("│ Содержимое дека в прямом порядке:  │\n");
    printf("╰────────────────────────────────────╯\n");
    if (isEmpty(deque))
    {
        printf("\n╭────────────────────────────╮\n");
        printf("│      Дек пуст...           │\n");
        printf("╰────────────────────────────╯\n");
        return;
    }
    while(current_2 != NULL)
    {
        printf("%d ", current_2->value);
        current_2 = current_2->Next;
    }
    printf("\n");
}


void deque_output(Deque* deque)
{
    if(isEmpty(deque))
    {
        printf("\n╭────────────────────────────╮\n");
        printf("│      Дек пуст...           │\n");
        printf("╰────────────────────────────╯\n");
        return;
    }

  printf("\n╭─────────────────────────────────────────────╮\n");
    printf("│ В каком формате вывести дек?                │\n");
    printf("│ В прямой последовательности - любая клавиша │\n");
    printf("│ В обратной последовательности - 1           │\n");
    printf("╰─────────────────────────────────────────────╯\n");
    printf("╰─> ");

    char user_input[50];
    deNode* current_1 = deque->back;
    deNode* current_2 = deque->begin;
    fgets(user_input, 50, stdin);

    switch (user_input[0]) {
        case '1':
            printf("\n╭────────────────────────────────────╮\n");
            printf("│ Содержимое дека в обратном порядке:│\n");
            printf("╰────────────────────────────────────╯\n");
            while(current_1 != NULL)
            {
                printf("%d ", current_1->value);
                current_1 = current_1->Prev;
            }
            printf("\n");
            break;

        default:
            deq_base_output(deque);
            break;
    }
}

void push_front(Deque* deque, int data)
{
    int deSize = get_size_deq(deque);
    if(deSize >= deque->max_size)
    {
      printf("\n╭──────────────────────────────────────────────────────────────╮\n");
        printf("│ Дек переполнен! Элемент %d не может быть добавлен.           │\n", data);
        printf("│ Максимальный размер: %d                                      │\n", deque->max_size);
        printf("╰──────────────────────────────────────────────────────────────╯\n");
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
        printf("\n╭──────────────────────────────────────────────────────────────╮\n");
        printf("│ Дек переполнен! Элемент %d не может быть добавлен.           │\n", data);
        printf("│ Максимальный размер: %d                                      │\n", deque->max_size);
        printf("╰──────────────────────────────────────────────────────────────╯\n");
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
    printf("\n╭────────────────────────────────────────────╮\n");
    printf("│ Выберите место добавления элемента в дек:  │\n");
    printf("│ В начало - 1                               │\n");
    printf("│ В конец - любая другая клавиша             │\n");
    printf("╰────────────────────────────────────────────╯\n");
    printf("╰─> ");

    char user_input[50];
    fgets(user_input, 50, stdin);

    switch (user_input[0]) {
        case '1':
            push_front(deque, value);
            printf("\n╭──────────────────────────────────────╮\n");
            printf("│ Элемент %3d успешно добавлен в начало │\n", value);
            printf("╰──────────────────────────────────────╯\n");

            break;

        default:
            push_back(deque, value);
            printf("\n╭──────────────────────────────────────╮\n");
            printf("│ Элемент %3d успешно добавлен в конец │\n", value);
            printf("╰──────────────────────────────────────╯\n");
            break;
    }
}

void deque_fill(Deque* deque)
{
    int current_size = get_size_deq(deque);
    if (current_size >= deque->max_size)
    {
        printf("\n╭───────────────────────────────────────────────╮\n");
        printf("│ Дек уже заполнен. Добавление невозможно.      │\n");
        printf("╰───────────────────────────────────────────────╯\n");
        return;
    }

    printf("\n╭────────────────────────────────────────────╮\n");
    printf("│           Заполнение дека                  │\n");
    printf("│ 1 - Вручную                                │\n");
    printf("│ Другое - Случайно                          │\n");
    printf("╰────────────────────────────────────────────╯\n");
    printf("╰─> ");

    char user_input[50];
    fgets(user_input, 50, stdin);

    switch (user_input[0]) {
        case '1':
            for (int i = 0; i < deque->max_size - current_size; i++) {
                printf("\n╭──────────────────────────────╮\n");
                printf("│ Введите число для добавления │\n");
                printf("╰──────────────────────────────╯\n");
                printf("╰─> ");
                int data = execute_verification(min_limit, max_limit);
                push_back(deque, data);
            }
            printf("\n╭──────────────────────────────────╮\n");
            printf("│  Дек был успешно заполнен!       │\n");
            printf("╰──────────────────────────────────╯\n");
            break;

        default:
            for (int i = 0; i < deque->max_size - current_size; i++) {
                int data = -100 + rand() % (100 - (-100) + 1);
                push_back(deque, data);
            }
            printf("\n╭──────────────────────────────────╮\n");
            printf("│  Дек был успешно заполнен!       │\n");
            printf("╰──────────────────────────────────╯\n");
            break;
    }
}

int pop_back(Deque* deque)
{
    if(isEmpty(deque))
    {
        printf("\n╭───────────────────────────────────────╮\n");
        printf("│ Дек пуст! Извлечение невозможно.      │\n");
        printf("╰───────────────────────────────────────╯\n");
        return -1;
    }

    deNode* temp = deque->back;
    int data = temp->value;
    deque->back = deque->back->Prev;

    if(deque->back == NULL)
    {
        deque->begin = NULL;
    }
    else
    {
        deque->back->Next = NULL;
    }

    free(temp);

    return data;
}

int pop_front(Deque* deque)
{
    if(isEmpty(deque))
    {
        printf("\n╭───────────────────────────────────────╮\n");
        printf("│ Дек пуст! Извлечение невозможно.      │\n");
        printf("╰───────────────────────────────────────╯\n");
        return -1;
    }

    deNode* temp = deque->begin;
    int data = temp->value;
    deque->begin = deque->begin->Next;

    if(deque->begin == NULL)
    {
        deque->back = NULL;
    }
    else
    {
        deque->begin->Prev = NULL;
    }

    free(temp);

    return data;
}

void deque_pop_menu(Deque* deque)
{
  printf("\n╭────────────────────────────────────────────╮\n");
    printf("│ Выберите место извлечения элемента из дека │\n");
    printf("│ Первый элемент - 1                         │\n");
    printf("│ Последний элемент - любая другая клавиша   │\n");
    printf("╰────────────────────────────────────────────╯\n");
    printf("╰─> ");

    char user_input[50];
    fgets(user_input, 50, stdin);

    if (deque->begin == NULL || deque->back == NULL)
    {
        printf("\n╭────────────────────────────────────────╮\n");
        printf("│     Дек пуст — извлечение невозможно!  │\n");
        printf("╰────────────────────────────────────────╯\n");
    }

    switch (user_input[0]) {
        case '1':
                printf("\n╭────────────────────────────────────────╮\n");
                printf("│ Извлечен первый элемент: %3d           │\n", deque->begin->value);
                printf("╰────────────────────────────────────────╯\n");
                pop_front(deque);
            break;

        default:
                printf("\n╭───────────────────────────────────────╮\n");
                printf("│ Извлечен последний элемент: %3d        │\n", deque->back->value);
                printf("╰───────────────────────────────────────╯\n");
                pop_back(deque);
            break;
    }
}

void clear_deque(Deque* deque)
{
    while(!isEmpty(deque))
    {
        pop_back(deque);
    }
  printf("\n╭────────────────────────────────╮\n");
    printf("│    Дек успешно очищен          │\n");
    printf("╰────────────────────────────────╯\n");
}

void special_deq_mode(Deque* deque)
{
    int running = 1;
    int count = 0;

    while(running) {
        if(isEmpty(deque))
        {
          printf("\n╭────────────────────────────╮\n");
            printf("│ Дек пуст... Выход...       │\n");
            printf("╰────────────────────────────╯\n");
            running = 0;
            break;
        }

        if (count >= 5)
        {
            printf("\n╭──────────────────────────────╮\n");
            printf("│     Желаете продолжить?      │\n");
            printf("│ 1 - Нет | Другая - Да        │\n");
            printf("╰──────────────────────────────╯\n");
            printf("╰─> ");

            char user_input[50];
            fgets(user_input, 50, stdin);

            switch (user_input[0]) {
                case '1':
                    running = 0;
                    break;

                default:
                    count = 0;
                    break;
            }
            continue;
        }

        deq_base_output(deque);
        printf("\n╭────────────────────────────────────╮\n");
        printf("│ Введите число для анализа:         │\n");
        printf("╰────────────────────────────────────╯\n");
        printf("╰─> ");
        int number = execute_verification(min_limit, max_limit);
        int value = pop_front(deque);
        if (number != value) {
            push_back(deque, number);
            printf("\n╭──────────────────────────────────────────────────────────────╮\n");
            printf("│ %d не совпал с элементом слева (%d) => он (%d) добавлен справа │\n", number, value, number);
            printf("╰──────────────────────────────────────────────────────────────╯\n");
            deq_base_output(deque);
        }
        else {
            printf("\n╭──────────────────────────────────────────────────────────────╮\n");
            printf("│ %d совпал с элементом слева (%d) => элемент слева удален     │\n", number, value);
            printf("╰──────────────────────────────────────────────────────────────╯\n");
            deq_base_output(deque);
        }
        count++;
    }
}

void deque_actions_menu()
{
    printf("\n╭────────────────────────────────────────────╮\n");
    printf("│ Введите максимальный размер дека:          │\n");
    printf("╰────────────────────────────────────────────╯\n");
    printf("╰─> ");
    int deque_size = execute_verification(0, max_limit);
    Deque* deque = create_deque(deque_size);
    int running = 1;

    while(running) {
      printf("\n╭────────────────────────────────────────────────────────────╮\n");
        printf("│ Выберите операцию для работы с деком:                      │\n");
        printf("│ 1 - Вывод дека на экран                                    │\n");
        printf("│ 2 - Заполнение дека                                        │\n");
        printf("│ 3 - Добавление элемента в дек                              │\n");
        printf("│ 4 - Извлечение элемента из дека                            │\n");
        printf("│ 5 - Узнать размер дека                                     │\n");
        printf("│ 6 - Режим удаления и совпадения                            │\n");
        printf("│ 7 - Стереть дек                                            │\n");
        printf("│ 8 - Выход                                                  │\n");
        printf("╰────────────────────────────────────────────────────────────╯\n");
        printf("╰─> ");

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
                    printf("\n╭──────────────────────────────────────────────────────────────╮\n");
                    printf("│ Дек переполнен! Нельзя добавить элемент.                    │\n");
                    printf("│ Максимальный размер: %d                                     │\n", deque->max_size);
                    printf("╰──────────────────────────────────────────────────────────────╯\n");
                    break;
                }
                printf("\n╭──────────────────────────────╮\n");
                printf("│ Введите число для добавления │\n");
                printf("╰──────────────────────────────╯\n");
                printf("╰─> ");
                int data = execute_verification(min_limit, max_limit);
                deque_push_menu(deque, data);

                break;

            case 4:
                deque_pop_menu(deque);
                break;

            case 5:
                printf("\n╭────────────────────────────────────╮\n");
                printf("│ Количество элементов дека: %3d     │\n", get_size_deq(deque));
                printf("╰────────────────────────────────────╯\n");
                break;

            case 6:
                clear_deque(deque);
                deque_fill(deque);
                special_deq_mode(deque);
                break;

            case 7:
                clear_deque(deque);
                break;

            case 8:
                printf("\n╭────────────────────────────╮\n");
                printf("│      Выход из меню...      │\n");
                printf("╰────────────────────────────╯\n");
                running = 0;
                break;
        }
    }
}