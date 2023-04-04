#include <stdio.h>
#include <stdlib.h>


int main() 
{
    // Для рандомайзера
    srand(time(NULL));

    // Размер массивов
    const int SIZE = 10;
    // Массивы
    int array1[SIZE];
    int array2[SIZE];

    // Заполнение массивов случайными числами от 0 до 9
    for (int i = 0; i < SIZE; i++)
    {
        array1[i] = rand() % 10;
        array2[i] = rand() % 10;
    }

    // Вывод содержимого первого массива
    printf("ARRAY #1: ");
    for (int i = 0; i < SIZE; i++)
        printf("%d  ", array1[i]);
    printf("\n");

    // Вывод содержимого второго массива
    printf("ARRAY #2: ");
    for (int i = 0; i < SIZE; i++)
        printf("%d  ", array2[i]);
    printf("\n");

    // Указатели на начала массивов
    int* a1 = &array1[0];
    int* a2 = &array2[0];

    // Результат перемножение и сложения
    int result;

    asm (
            // Перенос адресов массивов в регистры
            "mov %[a1], %%rsi;"
            "mov %[a2], %%rdi;"
            // Установка кол-во проходов
            "movl %[SIZE], %%ecx;"
            // Обнуление итогового результата
            "xorl %%ebx, %%ebx;"

            // Цикл перемножения и суммирование
        "ll:"
            // Взять значение из первого массива
            "movl (%%rsi), %%eax;"
            // Взять значение из второго массива
            "movl (%%rdi), %%edx;"
            // Перемножить их между собой (рез. сохраняется в eax)
            "mull %%edx;"
            // Суммировать это с конечным результатом
            "addl %%eax, %%ebx;"

            // Сместиться на след. эл. в массивах
            "addq $4, %%rdi;"
            "addq $4, %%rsi;"
            // Повторить действия ecx раз
            "loop ll;"

            // Записать итоговый результат в result
            "movl %%ebx, %[result];"
            :
            :[a1]"m"(a1), [a2]"m"(a2), [SIZE]"m"(SIZE), [result]"m"(result)
            :
        );

    // Вывод результата
    printf("RESULT = %d\n", result);

    return 0;

}

