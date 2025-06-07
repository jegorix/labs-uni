//
// Created by jegorix on 7.06.25.
//
#include <stdio.h>
#include <stdlib.h>
#include "validators.h"
#include "hashmap_functions.h"

int main()
{
   printf("Enter size of the hash-table: ");
   int table_size = execute_verification(1, max_limit);
   HashEntry* table = malloc(table_size * sizeof(HashEntry));

   char* key_1 = "apple";
   char* key_2 = "grape";

   insert(table, key_1, 5, table_size);
   insert(table, key_2, 7, table_size);

   search(table, key_1, table_size);
   search(table, key_2, table_size);



   for(int i = 0; i < table_size; i++)
   {
       free(table[i].key);
   }
   free(table);
   return 1;
}
