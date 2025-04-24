//
// Created by jegorix on 24.04.25.
//
#include "tree_lobby.h"
#include "default_tree.h"

int tree_work_menu(int choice)
{
    switch (choice)
    {
        case 1:
            default_tree_menu();
            break;

        case 3:
            printf("Выход...\n");
            return 3;
    }
}


