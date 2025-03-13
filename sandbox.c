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


    // struct Permissions program = {1, 0, 1, 0};

    // program.status &= 0;
    // program.debugger |= 1;
    // program.error ^= 1;


    // printf("program runs: %d, debugger runs: %d, errors: %d, access: %d\n", program.status, program.debugger, program.error, program.access);


    

    

    return 0;

}