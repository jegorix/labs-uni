// Найти и вывести остаток от деления целого числа на 2, не выполняя деления и не используя операцию взятия остатка от деления.
// Новицкий
// 11.03.2025

#include <stdio.h>

int main(void)
{
    int num;
    printf("Введите число: \n");
    scanf("%d", &num);

    int beg_num = num;

    if(num < 0)
    {
        num = -num;
    }


    while (num >= 0)
    {
        if (num == 1)
        {
            printf("Остаток от деления числа %d на 2 = 1 \n", beg_num);
            break;
        }

        if (num == 0)
        {
            printf("Остаток от деления числа %d на 2 = 0 \n", beg_num);
            break;
        }

        num -= 2;
    }
    
    printf("Проверка: %d\n", beg_num % 2);


    return 0;
}