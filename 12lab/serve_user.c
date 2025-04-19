//
// Created by jegorix on 18.04.25.
//

#include "serve_user.h"
#include "validators.h"
#include "queue_actions.h"
#include "deque_actions.h"

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

    }

    return 1;

}