#include <iostream>
#include <stdio.h>
#include <mpi.h>

using namespace std;

#define N1 4096
//#define N1 64
//#define N1 256
//#define N1 1024
//#define N1 4096
#define S1 10
#define max 10
int main(int argc, char** argv) {
    float A[N1], B[N1], C[N1], Y[N1];
    int rank, size;
    double time1, time2;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    printf("Rank %d, Size %d\n", rank, size);
    if (rank == 0) {
    // Инициализация всех исходных данных в нулевом процессе
    for (int i = 0; i < N1; i++) {
        A[i] = rand() % max;
        B[i] = rand() % max;
        C[i] = rand() % max;
    }
 
    time1 = MPI_Wtime(); // Определение времени начала обработки
    for (int cicl = 0; cicl < 10000; cicl++) { // Цикл кратности
        for (int i = 1; i < size; i++) {
            // Распределение элементов массивов между процессами
            MPI_Send(&A[(int)i * N1 / size], (int)N1 / size, MPI_FLOAT, i, 0, 
MPI_COMM_WORLD);
            MPI_Send(&B[(int)i * N1 / size], (int)N1 / size, MPI_FLOAT, i, 0, 
MPI_COMM_WORLD);
            MPI_Send(&C[(int)i * N1 / size], (int)N1 / size, MPI_FLOAT, i, 0, 
MPI_COMM_WORLD);
        }
        // Цикл вычислений
        for (int i = 0; i < N1 / size; i++) Y[i] = (A[i] + B[i] * S1 + C[i]) * A[i];
        // Сбор результатов в массив Y
        for (int i = 1; i < size; i++) MPI_Recv(&Y[(int)i * N1 / size], (int)N1 / 
size, MPI_FLOAT, i, 0, MPI_COMM_WORLD, &status);
    }
        time2 = MPI_Wtime(); // Определение времени конца обработки
        double time = time2 - time1;
        for (int i = 0; i < N1; i++) printf("%f\n", Y[i]); // Вывод результатов
        printf("TIME=%f\n", time);
    }
    else { // Для всех процессов, кроме нулевого
        for (int cicl = 0; cicl < 10000; cicl++) { // Цикл кратности
            // Прием массивов
            MPI_Recv(&A[(int)rank * N1 / size], (int)N1 / size, MPI_FLOAT, 0, 0, 
MPI_COMM_WORLD, &status);
            MPI_Recv(&B[(int)rank * N1 / size], (int)N1 / size, MPI_FLOAT, 0, 0, 
MPI_COMM_WORLD, &status);
            MPI_Recv(&C[(int)rank * N1 / size], (int)N1 / size, MPI_FLOAT, 0, 0, 
MPI_COMM_WORLD, &status);
            // Вычисления
            for (int i = rank * N1 / size; i < (rank + 1) * N1 / size; i++) Y[i] = (A[i] + B[i] * S1 + C[i]) * A[i];
            // Передача результатов нулевому процессу
            MPI_Send(&Y[(int)rank * N1 / size], (int)N1 / size, MPI_FLOAT, 0, 0, 
MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();
}