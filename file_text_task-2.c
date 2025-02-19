#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Распечатать второе и предпоследнее слова.



char* get_words()
{
    char* input = malloc(256 * sizeof(char));
    printf("Введите слова:\n");
    fgets(input, 256, stdin);
    return input;
}


void add_data(char* file_name, char* user_input)
{
    FILE* file = fopen(file_name, "w");
    if(file == NULL)
    {
        printf("Не удалось открыть файл!\n");
        return;
    }

    fputs(user_input, file);
    fclose(file);

}


void extract_words(char* file_name)
{
    FILE* file = fopen(file_name, "r");
    if(file == NULL)
    {
        printf("Не удалось открыть файл!\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    int file_size = ftell(file);
    rewind(file);
    
    char* buffer = malloc((file_size + 1) * sizeof(char));
    fread(buffer, sizeof(char), file_size, file);
    buffer[file_size + 1] = '\0';

    char* delimiters = " ,.!?";
    char* word = strtok(buffer, delimiters);

    char** words = malloc(50 * sizeof(char*));

    int count;
    for(count = 0; word != NULL; count++)
    {
        words[count] = word;
        word = strtok(NULL, delimiters);
    }

    printf("Второе слово: %s\n", words[1]);
    printf("Предпоследнее слово: %s\n", words[count-2]);
    
    for (int i = 0; i < count; i++)
    {
        free(words[i]);
    }

    free(*words);
    free(word);
    free(delimiters);


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
    extract_words(file_name);
    free(user_input);
    


}