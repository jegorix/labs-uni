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




Node* search_node(Node* node, int value)
{
    if(node == NULL) return NULL;
    if(node->data == value) return node;

    if(node->data > value)
    {
        return search_node(node->left, value);
    }

    return search_node(node->right, value);

}


Node* minValueNode(Node* node)
{
    if(node == NULL){return NULL;}

    while(node->left != NULL)
    {
        node = node->left;
    }
    return node;
}




Node* delete(Node* root, int value)
{
    if(root == NULL)
    {
        printf("\n╭──────────────────────────────────────────────╮\n");
        printf("│ Элемент со значением %3d не найден.           │\n", value);
        printf("╰──────────────────────────────────────────────╯\n");
        return NULL;
    }

    if(root->data > value)
    {
        root->left = delete(root->left, value);
    }
    else if(root->data < value)
    {
        root->right = delete(root->right, value);
    }
    else
    {
        if(root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }

       else if(root->left == NULL)
        {
            Node* temp = root->right;
            free(root);
            return temp;
        }

        else if(root->right == NULL)
        {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = delete(root->right, temp->data);


    }

    return root;

}

void clean_tree(Node* root)
{
    if(root == NULL) return;

   clean_tree(root->right);
   clean_tree(root->left);

   free(root);

}

void get_tree_size(Node* root, int* size)
{
    if(root == NULL) return;
    get_tree_size(root->left, size);
    (*size)++;
    get_tree_size(root->right, size);

}