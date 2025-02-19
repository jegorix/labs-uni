#include <stdio.h>
#include <stdlib.h>
// Распечатать второе и предпоследнее слова.



char* get_words()
{
    char* input = malloc(256 * sizeof(char));
    fgets(input, 256, stdin);
    return input;
}


void add_data(char* file_name, char* user_input)
{
    FILE* file = fopen(file_name, "w");
    if(file == NULL)
    {
        printf("Не удалось открыть файл!\n");
        return ;
    }

    fputs(user_input, file);
    fclose(file);

}


int main(int argc, char* argv[])
{

if (argc < 2)
    {
        printf("Использование: %s <file_name>\n", argv[0]);
        return 1;
    }

    char* file_name = argv[1];
    char* user_input = get_words();
    add_data(file_name, user_input);


}