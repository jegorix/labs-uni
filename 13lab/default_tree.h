//
// Created by jegorix on 24.04.25.
//

#ifndef INC_13LAB_DEFAULT_TREE_H
#define INC_13LAB_DEFAULT_TREE_H

#include "validators.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    int data;
    struct Node* left;
    struct Node* right;

}Node;



void default_tree_menu();
Node* create_tree_manually();


#endif //INC_13LAB_DEFAULT_TREE_H
