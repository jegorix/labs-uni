// С клавиатуры заполнить файл словами. Вывести содержимое файла на экран.
// Распечатать второе и предпоследнее слова.
// Поменять местами самое длинное слово и самое коротко.
#include <stdio.h>
#include <stdlib.h>
// #include <string.h>


void data_output(char* file_name)
{
    printf("\nВаши слова:\n");
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



char* get_words(void)
{
    char* input = malloc(256 * sizeof(char));
    printf("Введите слова:\n");
    fgets(input, 256, stdin);
    return input;
}



int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Использование: %s <file_name>\n", argv[0]);
        return 1;
    }

    char *file_name = argv[1];
    char* user_input = get_words();
    add_data(file_name, user_input);
    data_output(file_name);
    free(user_input);

    
return 0;

}