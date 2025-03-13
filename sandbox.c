#include <stdio.h>




struct Permissions
{
    unsigned int status: 1;
    unsigned int debugger: 1;
    unsigned int error: 1;
    unsigned int access: 1;
};

struct UserPermissons
{
    unsigned can_read: 1;
    unsigned can_write: 1;
    unsigned can_execute: 1; 
};

int main(void)
{
    // OR   |
    // XOR  ^
    // AND  &
    // NOT  ~
    // left shift <<
    // rigth shift >>

    struct UserPermissons current_user = {1, 0, 0};
    current_user.can_write |= 1;
    current_user.can_execute ^= 1;

    printf("Желаете изменить права поля?(1 - read, 2 - write, 3 - execute)\n");
    char user_choice;
    scanf("%c", &user_choice);



    switch (user_choice)
    {
        case '1':
        current_user.can_read ^= 1;
        printf("read status: %d\n", current_user.can_read);
        break;

        case '2':
        current_user.can_write ^= 1;
        printf("write status: %d\n", current_user.can_write);
        break;

        case '3':
        current_user.can_execute ^= 1;
        printf("execute status: %d\n", current_user.can_execute);
        break;

        default:
        printf("Неизвестный выбор\n");
        break;

    }



    printf("Read: %d, write: %d, can execute: %d\n", current_user.can_read, current_user.can_write, current_user.can_execute);




    // struct Permissions program = {1, 0, 1, 0};

    // program.status &= 0;
    // program.debugger |= 1;
    // program.error ^= 1;


    // printf("program runs: %d, debugger runs: %d, errors: %d, access: %d\n", program.status, program.debugger, program.error, program.access);



    return 0;

}