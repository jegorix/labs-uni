//
// Created by jegorix on 7.06.25.
//
#include <stdio.h>
#include <stdlib.h>
#include "validators.h"
#include "hashmap_functions.h"

int main()
{
    printf("Start HashMap work\n");

    HashMap* map = create_hashmap(2);
    insert(map, "Milk", 12);
    insert(map, "Water", 5);
    insert(map, "Eggs", 7);

    search(map, "Milk");
    search(map, "Water");
    search(map, "Eggs");

    freeHashMap(map);
}
