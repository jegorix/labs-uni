//
// Created by jegorix on 7.06.25.
//

#ifndef HASH_TABLE_HASHMAP_FUNCTIONS_H
#define HASH_TABLE_HASHMAP_FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct{
    char* key;
    int occupied;
    int value;
}HashEntry;

typedef struct{
    HashEntry* entries;
    int capacity;
    int size;
}HashMap;

int hash_function(const char* key, int table_size);
void insert(HashMap* map, const char* key, int value);
int search(HashMap* table, const char* key);
HashMap* create_hashmap(int initial_capacity);
void freeHashMap(HashMap* map);
void resize(HashMap* map);
void delete(HashMap* map, const char* key);

#endif //HASH_TABLE_HASHMAP_FUNCTIONS_H
