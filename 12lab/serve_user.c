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
    switch (user_choice) {
        case 1:
            printf("\nЗадача №1\n");
            queue_actions_menu();
            break;

        case 2:
            printf("\nЗадача №2\n");
            deque_actions_menu();
            break;

        case 3:
            printf("\nЗадача №3\n");
            queue_identity_menu();
            break;

        case 4:
            printf("\nВыход...\n");
            return 4;

        default:
            return 0;

    }

    return 1;

}