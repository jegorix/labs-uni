//
// Created by jegorix on 25.04.25.
//

#include "find_repeats.h"

void collect_values(Node* root, int* array, int* index)
{
    if(root == NULL) return;

    collect_values(root->left, array, index);
    array[*index] = root->data;
    (*index)++;
    collect_values(root->right, array, index);

}

void find_repeats(Node* root)
{
    int* array = malloc( max_limit * sizeof(int));
    int index = 0;
    collect_values(root, array, &index);

    int max_count = 1;
    int maxValue = array[0];

    for(int i = 0; i < index; i++)
    {
        int count = 1;
        for(int j = i + 1; j < index; j++)
        {
            if(array[i] == array[j])
            {
                count++;
            }
        }

        if(count > max_count)
        {
            max_count = count;
            maxValue = array[i];
        }
    }
    free(array);
    printf("\n╭────────────────────────────────────────────────────╮\n");
    printf("│ Элемент %3d встречается чаще всего: %2d раз(а).    │\n", maxValue, max_count);
    printf("╰────────────────────────────────────────────────────╯\n");

}