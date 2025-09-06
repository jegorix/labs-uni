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
            clearScreen();
            default_tree_menu();
            break;

        case 2:
            printf("\n╭────────────────────────╮\n");
            printf("│        Выход           │\n");
            printf("╰────────────────────────╯\n");
            return 2;
    }
}


