//
// Created by jegorix on 24.04.25.
//

//1. Написать программу для создания произвольного бинарного дерева.
//2. Произвести удаление элементов дерева, выбираемых пользователем.
//3. Выполнить задание по вариантам.
//4. Добавить визуализацию полученного дерева.

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
                    in_order_show(root);
                   break;

                case '2':
                    root = create_tree_hand_rand();
                    in_order_show(root);
                    break;




            }





}
