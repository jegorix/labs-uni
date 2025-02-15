// Найти самую длинную последовательность равных элементов.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// С клавиатуры заполнить файл целыми числами.


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

    FILE* file = fopen(file_name, "wb");

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
            int number =  rand() % 10 + 0;
            fwrite(&number, sizeof(int), 1, file);
    
        }
    
        fclose(file);
    
    }
    printf("Целые случайные числа успешно записаны!\n");

}




void find_max_length_sequense(char* file_name, int number_count)
{

FILE* file = fopen(file_name, "rb");

int prev_number, current_number;
int current_sequense = 1;
int max_sequense = 1;
int that_elem;

fread(&prev_number, sizeof(int), 1, file);
that_elem = prev_number;
printf("%d ", prev_number);

for(int i = 1; i < number_count; i++)
{
    fread(&current_number, sizeof(int), 1, file);
    printf("%d ", current_number);

    if(prev_number == current_number)
    {
        current_sequense++;
        if(current_sequense > max_sequense)
        {
            max_sequense = current_sequense;
            that_elem = current_number;
        }
    }
    else
    {
        current_sequense = 1;
    }

    prev_number = current_number;
}



// int* numbers = malloc(number_count * sizeof(int));
// for(int i = 0; i < number_count; i++)
// {
//     fread(&numbers[i], sizeof(int), 1, file);
// }

// fclose(file);


// int current_sequense = 1;
// int max_sequense = 1;
// int that_elem = numbers[0];

// for(int i = 1; i < number_count; i++)
// {
//     if(numbers[i] == numbers[i-1])
//     {
//         current_sequense++;
    
//         if(current_sequense > max_sequense)
//         {
//             max_sequense = current_sequense;
//             that_elem = numbers[i];
//         }

//     }

//     else
//     {
//         current_sequense = 1;
//     }


// }xw


printf("\nСамая длинная последовательность равных элементов: %d и они равны(=%d)\n", max_sequense, that_elem);


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


// printf("\nВаши числа:\n");


// FILE* file_r = fopen(file_name, "rb");

// if (file_r != NULL)
// {   
//     for(int i = 0; i < number_count; i++)
//     {
//         int number;
//         fread(&number, sizeof(int), 1, file_r);
//         printf("%d ", number);
//     }
//     printf("\n");

//     fclose(file_r);
// }


find_max_length_sequense(file_name, number_count);




free(user_choice);
free(file_name);
return 0;
}