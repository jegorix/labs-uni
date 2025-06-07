//
// Created by jegorix on 7.06.25.
//

#include "hashmap_functions.h"

int hash_function(const char* key, int table_size)
{
    assert(key != NULL);
    unsigned long hash = 5381;
    int c;
    while((c = *key++))
    {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % table_size;
}



void insert(HashEntry* table, const char* key, int value, int table_size)
{
    assert(table != NULL);
    int index = hash_function(key, table_size);
    int original_index = index;

    while(table[index].occupied)
    {
        if(strcmp(table[index].key, key) == 0)
        {
            table[index].value = value;
            printf("updated key = %s, value = %d\n", key, value);
            return;
        }
        index = (index + 1) % table_size;

        if(index == original_index)
        {
            printf("Hash table is full! Can't insert key: %s\n", key);
            return;
        }
    }
    table[index].key = malloc(strlen(key) + 1);
    assert(table[index].key != NULL);
    strcpy(table[index].key, key);
    table[index].value = value;
    table[index].occupied = 1;
}


int search(HashEntry* table, const char* key, int table_size)
{
    int index = hash_function(key, table_size);
    int original_index = index;

    while(table[index].occupied)
    {
        if(strcmp(table[index].key, key) == 0)
        {
            printf("table[%s] = %d\n", key, table[index].value);
            return table[index].value;
        }
        index = (index + 1) % table_size;
        if(index == original_index)break;
    }
    printf("Not found\n");
    return -1;

}
