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

int hash_function(const char* key, int table_size);
void insert(HashEntry* table, const char* key, int value, int table_size);
int search(HashEntry* table, const char* key, int table_size);

#endif //HASH_TABLE_HASHMAP_FUNCTIONS_H
