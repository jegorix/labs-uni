#include "queue_identity.h"
#include "deep_compare.h"


void queue_identity_menu() {
    printf("\n╭────────────────────────────────────────────╮\n");
    printf("│ Введите максимальный размер очереди №1:    │\n");
    printf("╰────────────────────────────────────────────╯\n");
    printf("╰─> ");
    int queue_size_1 = execute_verification(0, max_limit);
    Queue *queue_1 = create_queue(queue_size_1);

    printf("\n╭────────────────────────────────────────────╮\n");
    printf("│ Введите максимальный размер очереди №2:    │\n");
    printf("╰────────────────────────────────────────────╯\n");
    printf("╰─> ");
    int queue_size_2 = execute_verification(0, max_limit);
    Queue *queue_2 = create_queue(queue_size_2);

    int running = 1;

    while (running) {
        printf("\n╭────────────────────────────────────────────╮\n");
        printf("│ С какой очередью вы желаете работать?      │\n");
        printf("│ Очередь №1 - 1                             │\n");
        printf("│ Очередь №2 - 2                             │\n");
        printf("│ Выход - 3                                  │\n");
        printf("╰────────────────────────────────────────────╯\n");
        printf("╰─> ");

        int user_choice = execute_verification(1, 3);

        switch (user_choice) {
            case 1:
                handle_queue(queue_1, queue_2, user_choice);
                break;

            case 2:
                handle_queue(queue_2, queue_1, user_choice);
                break;

            case 3:
                printf("\n╭────────────────────────────╮\n");
                printf("│      Выход из меню...      │\n");
                printf("╰────────────────────────────╯\n");
                running = 0;
                break;
        }
    }
}