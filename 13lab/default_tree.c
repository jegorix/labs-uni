//
// Created by jegorix on 24.04.25.
//

//1. Написать программу для создания произвольного бинарного дерева.
//2. Произвести удаление элементов дерева, выбираемых пользователем.
//3. Выполнить задание по вариантам.
//4. Добавить визуализацию полученного дерева.
//7. Написать функцию, определяющую максимальное количество одинаковых
//        элементов бинарного дерева.

#include "default_tree.h"
#include "tree_functions.h"




Node* create_tree_manually()
{
    Node* root = NULL;
    printf("Введите количество элементов дерева:\n");
    printf(">> ");
    int count = execute_verification(0, max_limit);

    for(int i = 0; i < count; i++)
    {
        printf("Введите значение элемента:\n");
        int value = execute_verification(min_limit, max_limit);
        root = insert(root, value);

    }
    printf("Дерево успешно создано!\n");
    return root;

}

Node* create_tree_hand_rand()
{
    Node* root = NULL;
    printf("Введите количество элементов дерева:\n");
    printf(">> ");
    int count = execute_verification(0, max_limit);

    for(int i = 0; i < count; i++)
    {
        int value = rand() % (100 - 0 + 1) + 0;
        root = insert(root, value);
    }

    printf("Дерево успешно создано!\n");

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
    printf("Дерево успешно создано!\n");

    return root;
}



void output_menu(Node* root)
{
    printf("\nВыберите способ вывода:\n"
           "1 - По возрастанию\n"
           "2 - По убыванию\n"
           "3 - В виде дерева\n>> ");

    int choice = execute_verification(1,3);
    switch(choice)
    {
        case 1:
            printf("\nВывод дерева по возрастанию:\n");
            in_order_show(root);
            break;

        case 2:
            printf("\nВывод дерева по убыванию:\n");
            reversed_in_order_show(root);
            break;

        case 3:
            printf("В виде дерева:\n");
            as_tree_print(root, 0, 0);
    }
    printf("\n");




}



void default_tree_actions(Node* root)
{
    int running = 1;
    int value;

    while(running) {
        printf("\nВыберите действие\n"
               "1 - Создать дерево снова\n"
               "2 - Просмотреть содержимое дерева\n"
               "3 - Добавить элемент в дерево\n"
               "4 - Удалить элемент дерева\n"
               "5 - Найти элемент дерева\n"
               "6 - Максимальное количество одинаковых элементов бинарного дерева\n"
               "7 - Задача послойного обход бинарного дерева\n"
               "8 - Очистить дерево\n"
               "9 - Выход\n");

        int user_choice = execute_verification(0, 9);

        switch (user_choice)
        {
            case 0:
                in_order_show(root);
                break;

            case 1:
                default_tree_menu();
                break;

            case 2:
                output_menu(root);
                break;

            case 3:
                printf("\nВведите значение для добавления:\n>> ");
                value = execute_verification(min_limit, max_limit);
                root = insert(root, value);
                printf("Значение %d успешно добавлено!\n", value);
                break;

            case 9:
                printf("Выйти в главное меню");
                running = 0;
                break;



        }

    }


}






void default_tree_menu()
{
    Node* root = NULL;
    char user_choice[50];
    printf("\nВыберите способ создания дерева:\n"
            ">> 1 - Ручное создание\n"
            ">> 2 - Ручной ввод размера и случайное заполнение\n"
            ">> Любая другая клавиша - Полностью случайное создание\n\n");
            printf(">> ");
            fgets(user_choice, 50, stdin);

            switch (user_choice[0])
            {
                case '1':
                    root = create_tree_manually();
//                    in_order_show(root);
                   break;

                case '2':
                    root = create_tree_hand_rand();
//                    in_order_show(root);
                    break;

                default:
                    root = create_tree_rand();
//                    in_order_show(root);

            }

            default_tree_actions(root);




}
