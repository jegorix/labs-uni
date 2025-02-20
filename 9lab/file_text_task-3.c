#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Поменять местами самое длинное слово и самое короткое.



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




char** words_sep(char* file_name, int* count)
{
    FILE* file = fopen(file_name, "r");
    if(file == NULL)
    {
        printf("Не удалось открыть файл!\n");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    int file_size = ftell(file);
    rewind(file);

    char* buffer = malloc((file_size + 1) * sizeof(char));
    fread(buffer, sizeof(char), file_size, file);
    buffer[file_size] = '\0';

    fclose(file);

    char* delimiters = " ,.?!";
    char* word = strtok(buffer, delimiters);
    char** words = malloc(50 * sizeof(char*));

    for(*count = 0; word != NULL; (*count)++)
    {
        words[*count] = word;
        word = strtok(NULL, delimiters);

    }

    return words;

}


int identify_longest_word(char** words_array, int words_count)
{
    int longest_word_index = 0;
    for(int i = 1; i < words_count; i++)
    {
        if (strlen(words_array[longest_word_index]) < strlen(words_array[i]))
        {
            longest_word_index = i;

        }
    }
    printf("Самое длинное слово: %s\n", words_array[longest_word_index]);
    return longest_word_index;

}


int identify_shortest_word(char** words_array, int words_count)
{
    int shortest_word_index = 0;
    for(int i = 1; i < words_count; i++)
    {
        if (strlen(words_array[shortest_word_index]) > strlen(words_array[i]))
        {
            shortest_word_index = i;

        }
    }
    printf("Самое короткое слово: %s\n", words_array[shortest_word_index]);
    return shortest_word_index;

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
    }

    else
    {
        char* user_input = get_words();
        add_data(argv[1], user_input);
        data_output(argv[1]);
        free(user_choice);
    }

    int words_count = 0;
    char** words_array = words_sep(argv[1], &words_count) ;
    int long_index = identify_longest_word(words_array, words_count);
    int short_index = identify_shortest_word(words_array, words_count);
    printf("= %d\n", long_index);
    printf("= %d\n", short_index);


    
    free(words_array);



}