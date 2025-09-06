//
// Created by jegorix on 18.04.25.
//



#include "serve_user.h"
#include "validators.h"
#include "queue_actions.h"
#include "deque_actions.h"
#include "queue_identity.h"


int handle_user_choice(int user_choice)
{
    switch (user_choice)
    {
        case 1:
            printf(
                    "\n╭────────────────────────────╮\n"
                    "│         Задача №1          │\n"
                    "╰────────────────────────────╯\n"
            );
            queue_actions_menu();
            break;

        case 2:
            printf(
                    "\n╭────────────────────────────╮\n"
                    "│         Задача №2          │\n"
                    "╰────────────────────────────╯\n"
            );
            deque_actions_menu();
            break;

        case 3:
            printf(
                    "\n╭────────────────────────────╮\n"
                    "│         Задача №3          │\n"
                    "╰────────────────────────────╯\n"
            );
            queue_identity_menu();
            break;

        case 4:
            printf(
                    "\n╭────────────────────────────╮\n"
                    "│           Выход...         │\n"
                    "╰────────────────────────────╯\n"
            );
            return 4;

        default:
            printf(
                    "\n╭────────────────────────────────────╮\n"
                    "│    Некорректный выбор. Повторите. │\n"
                    "╰────────────────────────────────────╯\n"
            );
            return 0;
    }

    return 1;
}