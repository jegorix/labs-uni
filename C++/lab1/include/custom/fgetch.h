//
// Created by jegorix on 7.09.25.
//

#ifndef LAB1_FGETCH_H
#define LAB1_FGETCH_H

#include <iostream>
#include <termios.h>
#include <unistd.h>

char fgetch() {
    struct termios oldt, newt;
    char ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    read(STDIN_FILENO, &ch, 1);

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}

#endif //LAB1_FGETCH_H
