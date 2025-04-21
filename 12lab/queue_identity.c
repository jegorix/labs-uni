//
// Created by jegorix on 19.04.25.
//
//Проверьте на равенство две очереди. Решение в программе оформляйте через подпрограммы.
#include "queue_identity.h"
#include "deep_compare.h"





void queue_identity_menu() {
    printf("\nВведите максимальный размер очереди №1:\n");
    printf(">> ");
    int queue_size_1 = execute_verification(0, max_limit);
    Queue *queue_1 = create_queue(queue_size_1);

    printf("\nВведите максимальный размер очереди №2:\n");
    printf(">> ");
    int queue_size_2 = execute_verification(0, max_limit);
    Queue *queue_2 = create_queue(queue_size_2);

    int running = 1;

    while (running) {
        printf("\nС какой очередью вы желаете работать?\n"
               "Очередь №1 - 1\n"
               "Очередь №2 - 2\n"
               "Выход - 3\n");
        printf(">> ");

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