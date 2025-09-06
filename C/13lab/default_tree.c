//
// Created by jegorix on 24.04.25.
//
// 1. Написать программу для создания произвольного бинарного дерева.
// 2. Произвести удаление элементов дерева, выбираемых пользователем.
// 3. Выполнить задание по вариантам.
// 4. Добавить визуализацию полученного дерева.
// 7. Написать функцию, определяющую максимальное количество одинаковых элементов бинарного дерева.

#include "default_tree.h"
#include "tree_functions.h"
#include <time.h>

Node* create_tree_manually()
{
    Node* root = NULL;
    printf("\n╭────────────────────────────────────────────╮\n");
    printf("│ Введите количество элементов дерева:       │\n");
    printf("╰────────────────────────────────────────────╯\n");
    printf("╰─> ");
    int count = execute_verification(0, max_limit);

    for(int i = 0; i < count; i++)
    {
        printf("\n╭──────────────────────────────╮\n");
        printf("│ Введите значение элемента:   │\n");
        printf("╰──────────────────────────────╯\n");
        printf("╰─> ");
        int value = execute_verification(min_limit, max_limit);
        root = insert(root, value);
    }
    printf("\n╭────────────────────────────────╮\n");
    printf("│ Дерево успешно создано!        │\n");
    printf("╰────────────────────────────────╯\n");
    return root;
}

Node* create_tree_hand_rand()
{
    Node* root = NULL;
    printf("\n╭────────────────────────────────────────────╮\n");
    printf("│ Введите количество элементов дерева:       │\n");
    printf("╰────────────────────────────────────────────╯\n");
    printf("╰─> ");
    int count = execute_verification(0, max_limit);

    for(int i = 0; i < count; i++)
    {
        int value = rand() % (100 - 0 + 1) + 0;
        root = insert(root, value);
    }
    printf("\n╭────────────────────────────────╮\n");
    printf("│ Дерево успешно создано!        │\n");
    printf("╰────────────────────────────────╯\n");
    return root;
}

Node* create_tree_rand()
{
    Node* root = NULL;
    int count = rand() % (30 - 5 + 1) + 5;
    for(int i = 0; i < count; i++)
    {
        int value = rand() % (100 - 0 + 1) + 0;
        root = insert(root, value);
    }
    printf("\n╭────────────────────────────────╮\n");
    printf("│ Дерево успешно создано!        │\n");
    printf("╰────────────────────────────────╯\n");
    return root;
}



void output_menu(Node* root)
{
    printf("\n╭────────────────────────────────────────────╮\n");
    printf("│ Выберите способ вывода:                    │\n");
    printf("│ 1 - По возрастанию                         │\n");
    printf("│ 2 - По убыванию                            │\n");
    printf("│ 3 - В виде дерева                          │\n");
    printf("╰────────────────────────────────────────────╯\n");
    printf("╰─> ");

    int choice = execute_verification(1, 3);
    switch(choice)
    {
        case 1:
            printf("\n╭────────────────────────────────────╮\n");
            printf("│ Вывод дерева по возрастанию:       │\n");
            printf("╰────────────────────────────────────╯\n");
            in_order_show(root);
            break;

        case 2:
            printf("\n╭────────────────────────────────────╮\n");
            printf("│ Вывод дерева по убыванию:          │\n");
            printf("╰────────────────────────────────────╯\n");
            reversed_in_order_show(root);
            break;

        case 3:
            printf("\n╭────────────────────────────╮\n");
            printf("│ В виде дерева:             │\n");
            printf("╰────────────────────────────╯\n");
            as_tree_print(root, 0, 0);
    }
    printf("\n");
}



void default_tree_actions(Node* root)
{
    clearScreen();
    int running = 1;
    int value;

    while(running) {
        printf("\n╭────────────────────────────────────────────────────────────╮\n");
        printf("│ Выберите действие:                                         │\n");
        printf("│ 0 - Размер дерева                                          │\n");
        printf("│ 1 - Создать дерево снова                                   │\n");
        printf("│ 2 - Просмотреть содержимое дерева                          │\n");
        printf("│ 3 - Добавить элемент в дерево                              │\n");
        printf("│ 4 - Удалить элемент дерева                                 │\n");
        printf("│ 5 - Найти элемент дерева                                   │\n");
        printf("│ 6 - Максимальное количество одинаковых элементов           │\n");
        printf("│ 7 - Очистить дерево                                        │\n");
        printf("│ 8 - Выход                                                  │\n");
        printf("╰────────────────────────────────────────────────────────────╯\n");
        printf("╰─> ");

        int user_choice = execute_verification(0, 8);

        switch (user_choice)
        {
            case 0:
                if(root == NULL) {
                    printf("\n╭────────────────────────────╮\n");
                    printf("│      Дерево пусто...       │\n");
                    printf("╰────────────────────────────╯\n");
                    break;
                }
                int size = 0;
                get_tree_size(root, &size);
                printf("\n╭────────────────────────────────────╮\n");
                printf("│ Размер дерева: %3d                 │\n", size);
                printf("╰────────────────────────────────────╯\n");
                break;

            case 1:
                default_tree_menu();
                return;

            case 2:
                if(root == NULL) {
                    printf("\n╭────────────────────────────╮\n");
                    printf("│      Дерево пусто...       │\n");
                    printf("╰────────────────────────────╯\n");
                    break;
                }
                output_menu(root);
                break;

            case 3:
              printf("\n╭──────────────────────────────────╮\n");
                printf("│ Введите значение для добавления: │\n");
                printf("╰──────────────────────────────────╯\n");
                printf("╰─> ");
                value = execute_verification(min_limit, max_limit);
                root = insert(root, value);
              printf("\n╭──────────────────────────────────────╮\n");
                printf("│ Значение %3d успешно добавлено!      │\n", value);
                printf("╰──────────────────────────────────────╯\n");
                break;

            case 4:
                if(root == NULL) {
                    printf("\n╭────────────────────────────╮\n");
                    printf("│      Дерево пусто...       │\n");
                    printf("╰────────────────────────────╯\n");
                    break;
                }
                printf("\n╭────────────────────────────────────────────╮\n");
                printf("│ Введите значение элемента для удаления:    │\n");
                printf("╰────────────────────────────────────────────╯\n");
                printf("╰─> ");
                value = execute_verification(min_limit, max_limit);
                Node* found = search_node(root, value);
                if(found != NULL) {
                    printf("\n╭──────────────────────────────────────╮\n");
                    printf("│ Элемент %3d успешно удален!          │\n", value);
                    printf("╰──────────────────────────────────────╯\n");
                }
                else {
                    printf("\n╭──────────────────────────────────────╮\n");
                    printf("│ Элемент %3d не найден!               │\n", value);
                    printf("╰──────────────────────────────────────╯\n");
                }
                root = delete(root, value);
                break;

            case 5:
                if(root == NULL) {
                    printf("\n╭────────────────────────────╮\n");
                    printf("│      Дерево пусто...       │\n");
                    printf("╰────────────────────────────╯\n");
                    break;
                }
                printf("\n╭────────────────────────────────────╮\n");
                printf("│ Введите элемент для поиска:        │\n");
                printf("╰────────────────────────────────────╯\n");
                printf("╰─> ");
                value = execute_verification(min_limit, max_limit);
                Node* temp = search_node(root, value);
                if(temp != NULL) {
                    printf("\n╭──────────────────────────────────────╮\n");
                    printf("│ Элемент со значением %3d найден!    │\n", value);
                    printf("╰──────────────────────────────────────╯\n");
                }
                else {
                    printf("\n╭──────────────────────────────────────╮\n");
                    printf("│ Элемент со значением %3d не найден! │\n", value);
                    printf("╰──────────────────────────────────────╯\n");
                }
                break;

            case 6:
                if(root == NULL) {
                    printf("\n╭────────────────────────────╮\n");
                    printf("│      Дерево пусто...       │\n");
                    printf("╰────────────────────────────╯\n");
                    break;
                }
                find_repeats(root);
                break;

            case 7:
                if(root == NULL) {
                  printf("\n╭────────────────────────────────────────────╮\n");
                    printf("│    Дерево уже было очищено ранее...        │\n");
                    printf("╰────────────────────────────────────────────╯\n");
                    break;
                }
                clean_tree(root);
              printf("\n╭────────────────────────────────╮\n");
                printf("│     Дерево успешно очищено     │\n");
                printf("╰────────────────────────────────╯\n");
                root = NULL;
                break;

            case 8:
                printf("\n╭────────────────────────────╮\n");
                printf("│ Выйти в главное меню...    │\n");
                printf("╰────────────────────────────╯\n");
                running = 0;
                break;
        }
    }
}

void default_tree_menu()
{
    clearScreen();
    srand(time(NULL));
    Node* root = NULL;
    char user_choice[50];
    printf("\n╭────────────────────────────────────────────────────────────╮\n");
    printf("│ Выберите способ создания дерева:                           │\n");
    printf("│ 1 - Ручное создание                                        │\n");
    printf("│ 2 - Ввод размера и случайное заполнение                    │\n");
    printf("│ Другая клавиша - Полностью случайное создание              │\n");
    printf("╰────────────────────────────────────────────────────────────╯\n");
    printf("╰─> ");
    fgets(user_choice, 50, stdin);

    switch (user_choice[0])
    {
        case '1':
            root = create_tree_manually();
            break;

        case '2':
            root = create_tree_hand_rand();
            break;

        default:
            root = create_tree_rand();
    }

    default_tree_actions(root);
}