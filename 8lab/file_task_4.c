#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Отсортировать файл таким образом – четные слева, нули посередине, нечетные
// справа. Порядок следования элементов не изменять. Доп массивов не
// использовать


int exceute_verification(int min, int max)
{
    while(1)
    {
        char input[100];
        int number;
        char symbol;

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("Ошибка ввода! Попробуйте еще раз.\n");
            continue;
        }

        if (sscanf(input, "%d %c", &number, &symbol) != 1)
        {
            printf("Ошибка ввода! Введите целое число!\n");
            continue;

        }

        if (number > max || number < min)
        {
            printf("Введите целое число, удовлетворяющее диапазону [%d, %d]\n", min, max);
            continue;
        }

        return number;

    }
}





char* user_name_input(void)
{
    char* str = NULL;
    char ch;

    int length = 0;
    int capacity = 10;

    str = malloc(sizeof(char) * capacity);

    while((ch = getchar()) != '\n')
    {
        if(length + 1 >= capacity)
        {
            capacity *= 2;
            str = realloc(str, capacity * sizeof(char));
        }

        str[length++] = ch;
    }
    str[length] = '\0';

    return str;

}


void write_to_file_by_hand(char* file_name, int number_count)
{

    FILE* file = fopen(file_name, "r+b");

    if (file != NULL)
    {
        for(int i = 0; i < number_count; i++)
        {
            printf("Введите %d-e число для записи в файл:\n", i+1);
            int number = exceute_verification(-2147483647, 2147483647);
            fwrite(&number, sizeof(int), 1, file);
    
        }
    
        fclose(file);
    
    }
    printf("Целые числа успешно записаны!\n");

}



void write_to_file_by_random(char* file_name, int number_count)
{

    FILE* file = fopen(file_name, "wb");

    if (file != NULL)
    {
        for(int i = 0; i < number_count; i++)
        {
            int number = rand() % 10;
            fwrite(&number, sizeof(int), 1, file);
    
        }
    
        fclose(file);
    
    }
    printf("Целые случайные числа успешно записаны!\n");

}



void file_data_output(char* file_name, int number_count)
{
printf("\nВаши числа:\n");

FILE* file_r = fopen(file_name, "rb");

if (file_r != NULL)
{   
    for(int i = 0; i < number_count; i++)
    {
        int number;
        fread(&number, sizeof(int), 1, file_r);
        printf("%d ", number);
    }
    printf("\n");

    fclose(file_r);
}

}





void hybrid_sort(char* file_name, int numbers_count)
{
    FILE* file = fopen(file_name, "r+b");

    int current_number;
    int zero_pos = 0;
    int even_pos = 0;
    int odd_pos = numbers_count - 1;

    while(zero_pos <= odd_pos)
    {
        fseek(file, zero_pos * sizeof(int), SEEK_SET);
        fread(&current_number, sizeof(int), 1, file);

        if(current_number % 2 == 0 && current_number != 0)
        {   
            if(zero_pos != even_pos)
            {
                int temp;
                fseek(file, even_pos * sizeof(int), SEEK_SET);
                fread(&temp, sizeof(int), 1, file); // что лежит на позиции even_pos

                // меняю местами содержимое zero и even
                // even в начало / zero вперед
                fseek(file, zero_pos * sizeof(int), SEEK_SET); 
                fwrite(&temp, sizeof(int), 1, file); 

                fseek(file, even_pos * sizeof(int), SEEK_SET);
                fwrite(&current_number, sizeof(int), 1, file);

            }
            even_pos++;
            zero_pos++;
        }


        else if(current_number == 0)
        {
            zero_pos++;
        }

        else
        {
            if(current_number % 2 != 0)
            {
                if(zero_pos != odd_pos) // не нужно менять, если нечет уже в конце
                {
                    int temp;
                    fseek(file, odd_pos * sizeof(int), SEEK_SET);
                    fread(&temp, sizeof(int), 1, file);
                    
                    fseek(file, zero_pos * sizeof(int), SEEK_SET);
                    fwrite(&temp, sizeof(int), 1, file);

                    fseek(file, odd_pos * sizeof(int), SEEK_SET);
                    fwrite(&current_number, sizeof(int), 1, file);

                }
            }

            odd_pos--;

        }

    }

    fclose(file);


}



int main(void)
{
srand(time(NULL));

printf("Введите имя файла:\n");
char* file_name = user_name_input();

printf("Введите количество целых чисел, которое вы хотите поместить в файл:\n");
int number_count = exceute_verification(0, 2147483647);

printf("Как вы хотите записать данные?(1 - вручную, любая другая клавиша - случайные числа)\n");
char* user_choice = user_name_input();

if(user_choice[0] == '1')
{
    write_to_file_by_hand(file_name, number_count);
}
else
{
    write_to_file_by_random(file_name, number_count);
}



file_data_output(file_name, number_count);

hybrid_sort(file_name, number_count);

file_data_output(file_name, number_count);

free(user_choice);
free(file_name);
return 0;
}







