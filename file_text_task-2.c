#include <stdio.h>
#include <stdlib.h>
// Распечатать второе и предпоследнее слова.



char* get_words()
{
    char* input = malloc(256 * sizeof(char));
    fgets(input, sizeof(256), stdin);
    return input;
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
    

}