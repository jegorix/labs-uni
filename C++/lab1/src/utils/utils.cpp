//
// Created by jegorix on 7.09.25.
//
#include <unistd.h>
#include "../../include/utils.h"
#include <iostream>

void clearScreen()
{
    system("clear");
}

void loadingAnimation(int dots, int delay_ms)
{
    for(int i = 0; i < dots; i++)
    {
        std::cout << ".";
        std::cout.flush();
        usleep(delay_ms * 1000);
    }
    std::cout << std::endl;
}
