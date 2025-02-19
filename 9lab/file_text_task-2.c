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
    buffer[file_size] = '\0';

    char* delimiters = " ,.!?";
    char* word = strtok(buffer, delimiters);

    char** words = malloc(50 * sizeof(char*));

    int count;
    for(count = 0; word != NULL; count++)
    {
        words[count] = word;
        word = strtok(NULL, delimiters);
    }

    printf("\nВторое слово: %s\n", words[1]);
    printf("Предпоследнее слово: %s\n", words[count-2]);
    


    free(words);
    free(buffer);

    fclose(file);

}



void data_output(char* file_name)
{
    printf("\nСодержимое файла:\n");
    FILE* file = fopen(file_name, "r");
    if(file == NULL)
    {
        printf("Не удалось открыть файл!\n");
        return ;
    }

    char ch;
    while((ch = fgetc(file)) != EOF)
    {
        putchar(ch);
    }


    fclose(file);
}






int main(int argc, char* argv[])
{

if (argc < 2)
    {
        printf("Использование: %s <file_name>\n", argv[0]);
        return 1;
    }
    // argv[1] =--= file_name

    printf("\nВы хотите считать данные?( нажмите 1 )\n");
    printf("Или записать новые и получить результат?( любая клавиша )\n");

    char* user_choice = malloc(256 * sizeof(char));
    fgets(user_choice, 256, stdin);

    if(user_choice[0] == '1')
    {
        data_output(argv[1]);
        extract_words(argv[1]);
    }

    else
    {
        char* user_input = get_words();
        add_data(argv[1], user_input);
        extract_words(argv[1]);
    }

    free(user_choice);

}