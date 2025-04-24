//
// Created by jegorix on 24.04.25.
//

#include "tree_functions.h"
Node* createNode(int value)
{
    Node* newNode = malloc(sizeof(Node));
    if(newNode != NULL)
    {
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->data = value;
    }
    return newNode;
}



Node* insert(Node* root, int value)
{
    if(root == NULL)
    {
        return createNode(value);
    }

    if(value >= root->data)
    {
        root->right = insert(root->right, value);
    }

    else if(value <= root->data)
    {
        root->left = insert(root->left, value);
    }

    return root;
}


void in_order_show(Node* root)
{
    if(root == NULL)
    {
        return;
    }

    in_order_show(root->left);
    printf("%d ", root->data);
    in_order_show(root->right);
}

void reversed_in_order_show(Node* root)
{
    if(root == NULL)
    {
        return;
    }
    reversed_in_order_show(root->right);
    printf("%d ", root->data);
    reversed_in_order_show(root->left);

}

void as_tree_print(Node* root, int space, int isRight)
{
    if(root == NULL){return;}

    int delta = 5;
    space += delta;

    as_tree_print(root->right, space, 1);
    printf("\n");
    for(int i = delta; i < space; i++){printf(" ");}

    if(space > delta)
    {
        if(isRight){printf("/ ");}
        else{printf("\\ ");}
    }

    printf("%d\n", root->data);
    as_tree_print(root->left, space, 0);

}