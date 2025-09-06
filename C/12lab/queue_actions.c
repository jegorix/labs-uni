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

  printf("\n╭────────────────────────────────────────────╮\n");
    printf("│  Очередь успешно создана, ее размер = %3d  │\n", queue_size);
    printf("╰────────────────────────────────────────────╯\n");
    printf("╰─> ");
    return queue;
}



void queue_output(Queue* queue)
{
    Node* current = queue->begin;

  printf("\n╭────────────────────────────╮\n");
    printf("│     Содержимое очереди     │\n");
    printf("╰────────────────────────────╯\n");

    if (current == NULL)
    {
      printf("\n╭────────────────────────────╮\n");
        printf("│      Очередь пуста...      │\n");
        printf("╰────────────────────────────╯\n");
        return;
    }

    while (current != NULL)
    {
        printf("%d ", current->value);
        current = current->Next;
    }

    printf("\n");
}



int get_size(Queue* queue)
{
    int q_size = 0;
    Node* current = queue->begin;

    while (current != NULL)
    {
        q_size++;
        current = current->Next;
    }

    return q_size;
}



void queue_push(Queue* queue, int value)
{
    int current_size = get_size(queue);

    if (current_size >= queue->max_size)
    {
      printf("\n╭──────────────────────────────────────────────────────────────╮\n");
        printf("│ Очередь переполнена! Элемент %d не может быть добавлен.       │\n", value);
        printf("│ Максимальный размер: %d                                       │\n", queue->max_size);
        printf("╰──────────────────────────────────────────────────────────────╯\n");
        return;
    }

    Node* new_node = malloc(sizeof(Node));
    new_node->value = value;
    new_node->Next = NULL;

    if (queue->back == NULL)
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



void queue_fill(Queue* queue)
{
    int current_size = get_size(queue);

    if (current_size >= queue->max_size)
    {
      printf("\n╭───────────────────────────────────────────────╮\n");
        printf("│ Очередь уже заполнена. Добавление невозможно. │\n");
        printf("╰───────────────────────────────────────────────╯\n");
        return;
    }

  printf("\n╭────────────────────────╮\n");
    printf("│  Заполнение очереди    │\n");
    printf("╰────────────────────────╯\n");
    printf("│ 1 - Вручную            │\n");
    printf("│ Другое - Случайно      │\n");
    printf("╰────────────────────────╯\n");
    printf("╰─> ");

    char user_input[50];
    fgets(user_input, 50, stdin);

    switch (user_input[0])
    {
        case '1':
            for (int i = 0; i < queue->max_size; i++)
            {
              printf("\n╭──────────────────────────────╮\n");
                printf("│ Введите число для добавления │\n");
                printf("╰──────────────────────────────╯\n");
                printf("╰─> ");
                int data = execute_verification(min_limit, max_limit);
                queue_push(queue, data);
            }
            break;

        default:
            for (int i = 0; i < queue->max_size; i++)
            {
                int data = -100 + rand() % 201;
                queue_push(queue, data);
            }
            break;
    }

  printf("\n╭──────────────────────────────────╮\n");
    printf("│  Очередь была успешно заполнена! │\n");
    printf("╰──────────────────────────────────╯\n");
}



int queue_pop(Queue* queue)
{
    if (queue->begin == NULL)
    {
      printf("\n╭────────────────────────────╮\n");
        printf("│ Очередь пуста!             │\n");
        printf("│ Извлечение невозможно.     │\n");
        printf("╰────────────────────────────╯\n");
        return -1;
    }

    Node* temp = queue->begin;
    int data = temp->value;

    queue->begin = queue->begin->Next;

    if (queue->begin == NULL)
    {
        queue->back = NULL;
    }

    free(temp);
    return data;
}


void clear_queue(Queue* queue)
{
    while (queue->begin != NULL)
    {
        queue_pop(queue);
    }
}


void special_mode(Queue* queue)
{
    char user_choice[50];
    int running = 1;

    while (running)
    {
        if (queue->back == NULL || queue->begin == NULL)
        {
            return;
        }

      printf("\n╭────────────────────────────────────╮\n");
        printf("│ Введите элемент для сравнения:     │\n");
        printf("╰────────────────────────────────────╯\n");
        printf("╰─> ");

        int check_number = execute_verification(min_limit, max_limit);

        if (check_number == queue->begin->value)
        {
            queue_push(queue, check_number);
            printf("\n╭──────────────────────────────────────────────────────╮\n");
            printf("│ %d совпал с первым элементом => добавлен в конец     │\n", check_number);
            printf("╰──────────────────────────────────────────────────────╯\n");
            queue_output(queue);

          printf("\n╭──────────────────────────────╮\n");
            printf("│     Желаете продолжить?      │\n");
            printf("│   1 - Нет   |   Другая - Да  │\n");
            printf("╰──────────────────────────────╯\n");
            printf("╰─> ");

            fgets(user_choice, 50, stdin);

            if (user_choice[0] == '1')
                running = 0;
        }
        else
        {
            int removed = queue_pop(queue);
          printf("\n╭──────────────────────────────────╮\n");
            printf("│ Удален элемент очереди: %d       │\n", removed);
            printf("╰──────────────────────────────────╯\n");
            queue_output(queue);
        }
    }
}


void queue_actions_menu()
{
  printf("\n╭────────────────────────────────────────────╮\n");
    printf("│ Введите максимальный размер очереди:       │\n");
    printf("╰────────────────────────────────────────────╯\n");
    printf("╰─> ");

    int queue_size = execute_verification(0, max_limit);

    Queue* queue = create_queue(queue_size);
    int catch;
    int running = 1;

    while (running)
    {
        printf("\n╭────────────────────────────────────────────────────────────╮\n");
        printf("│ Выберите операцию:                                         │\n");
        printf("│ 1 - Вывод очереди на экран                                 │\n");
        printf("│ 2 - Заполнение очереди                                     │\n");
        printf("│ 3 - Добавление элемента в очередь                          │\n");
        printf("│ 4 - Извлечение элемента очереди                            │\n");
        printf("│ 5 - Узнать размер очереди                                  │\n");
        printf("│ 6 - Режим удаления и совпадения                            │\n");
        printf("│ 7 - Стереть очередь                                        │\n");
        printf("│ 8 - Выход                                                  │\n");
        printf("╰────────────────────────────────────────────────────────────╯\n");

        printf(
              "\n╭───────────────────────────────────╮\n"
                "│        Введите команду:           │\n"
                "╰───────────────────────────────────╯\n"
                "╰─> "
        );

        int user_input = execute_verification(1, 8);

        switch (user_input)
        {
            case 1:
                queue_output(queue);
                break;

            case 2:
                queue_fill(queue);
                break;

            case 3:
              printf("\n╭──────────────────────────────╮\n");
                printf("│ Введите число для добавления │\n");
                printf("╰──────────────────────────────╯\n");
                printf("╰─> ");
                int data = execute_verification(min_limit, max_limit);
                queue_push(queue, data);

              printf("\n╭────────────────────────────────────╮\n");
                printf("│      Число успешно добавлено!      │\n");
                printf("╰────────────────────────────────────╯\n");
                break;

            case 4:
                catch = queue_pop(queue);
                if (catch != -1)
                {
                  printf("\n╭───────────────────────────────────────╮\n");
                    printf("  Первый элемент в очереди: %d           \n", catch);
                    printf("╰───────────────────────────────────────╯\n");
                }
                break;

            case 5:
              printf("\n╭────────────────────────────────────╮\n");
                printf("  Размер очереди: %d                \n", get_size(queue));
                printf("╰────────────────────────────────────╯\n");
                break;

            case 6:
                clear_queue(queue);
                queue_fill(queue);
                special_mode(queue);
                break;

            case 7:
                clear_queue(queue);
              printf("\n╭────────────────────────────────╮\n");
                printf("│    Очередь успешно очищена     │\n");
                printf("╰────────────────────────────────╯\n");
                break;

            case 8:
              printf("\n╭────────────────────╮\n");
                printf("│  Выход из меню...  │\n");
                printf("╰────────────────────╯\n");
                running = 0;
                break;
        }
    }
}