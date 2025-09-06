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



void insert(HashMap* map, const char* key, int value)
{
    if( (float)map->size / map->capacity > 0.7 )
    {
        resize(map);
        printf("resized!\n");
    }

    int index = hash_function(key, map->capacity);

    while(map->entries[index].occupied)
    {
        if(strcmp(map->entries[index].key, key) == 0)
        {
            map->entries[index].value = value;
            printf("updated key = %s, value = %d\n", key, value);
            return;
        }

        index = (index + 1) % map->capacity;

    }
    map->entries[index].key = malloc(strlen(key) + 1);
    assert(map->entries[index].key != NULL);
    strcpy(map->entries[index].key, key);
    map->entries[index].value = value;
    map->entries[index].occupied = 1;
    map->size++;
}


int search(HashMap* map, const char* key)
{
    int index = hash_function(key, map->capacity);
    int original_index = index;

    while(map->entries[index].occupied)
    {
        if(strcmp(map->entries[index].key, key) == 0)
        {
            printf("Dict[%s] = %d$\n", key, map->entries[index].value);
            return map->entries[index].value;
        }
        index = (index + 1) % map->capacity;
        if(index == original_index)break;
    }
    printf("Not found\n");
    return -1;

}



HashMap* create_hashmap(int initial_capacity)
{
    HashMap* map = malloc(sizeof(HashMap));
    assert(map != NULL);

    map->capacity = initial_capacity;
    map->size = 0;
    map->entries = malloc(initial_capacity * sizeof(HashEntry));

    for(int i = 0; i < initial_capacity; i++)
    {
        map->entries[i].key = NULL;
        map->entries[i].value = 0;
        map->entries[i].occupied = 0;
    }
    return map;

}




void freeHashMap(HashMap* map)
{
    for(int i = 0; i < map->capacity; i++)
    {
        if(map->entries[i].occupied)
        {
            free(map->entries[i].key);
        }

    }
    free(map->entries);
    free(map);
}





void resize(HashMap* map)
{
    int old_capacity = map->capacity;
    int new_capacity = old_capacity * 2;

    HashEntry* new_entries = malloc(new_capacity * sizeof(HashEntry));
    assert(new_entries != NULL);

    for(int i = 0; i < new_capacity; i++)
    {
        new_entries[i].occupied = 0;
        new_entries[i].key = NULL;
        new_entries[i].value = 0;
    }

    HashEntry* old_entries = map->entries;

    map->entries = new_entries;
    map->capacity = new_capacity;
    map->size = 0;

    for(int i = 0; i < old_capacity; i++)
    {
        if(old_entries[i].occupied) {
            insert(map, old_entries[i].key, old_entries[i].value);
            free(old_entries[i].key);
        }
    }
    free(old_entries);
}

//void delete(HashMap* map, const char* key)
//{
//
//}

