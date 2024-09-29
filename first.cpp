#include <iostream>
#include <stdio.h>

using namespace std;

#define N1 8
#define S1 10
#define max 10

int main(int argc, char** argv)
{
    float A[N1], B[N1], C[N1], Y[N1];
    // Инициализация исходных данных
    for (int i = 0; i < N1; i++)
    {
        A[i] = rand() % max;
        B[i] = rand() % max;
        C[i] = rand() % max;
    }
 
    // Вычисления
    for (int i = 0; i < N1; i++) Y[i] = (A[i] + B[i] * S1 + C[i]) * A[i];
    //Вывод результатов
    for (int i = 0; i < N1; i++) printf("Y[%d] = %f;\n ", i, Y[i]);
}