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