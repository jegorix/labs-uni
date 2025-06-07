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
    if(!table[index].occupied)
    {
        table[index].key = malloc(strlen(key) + 1);
        strcpy(table[index].key, key);
        table[index].value = value;
        table[index].occupied = 1;
        printf("inserted key = %s, value = %d\n", key, value);
    }
    else
    {
        printf("Collision found\n");
    }
}

int search(HashEntry* table, const char* key, int table_size)
{
    int index = hash_function(key, table_size);
    if(table[index].occupied && !strcmp(table[index].key, key))
    {
        printf("table[%s] = %d\n", key, table[index].value);
    }
    else
    {
        printf("Not found\n");
    }

}
