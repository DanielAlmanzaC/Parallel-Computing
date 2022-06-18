#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// gcc -g -Wall -fopenmp -o Practica9 Practica9.c -lm
// ./Practica9 4
int numeroDeHilos;
int n = 10000000;
int sum = 0;
int matrix_1[10000000];
int matrix_2[10000000];
int matrix_3[10000000];
void sum_mat(int * matrix_1,int * matrix_2, int * matrix_3); /*Funcion del Hilo*/
int main(int argc, char *argv[])
{
    numeroDeHilos = strtol(argv[1], NULL, 10);
    for(int i=0; i<n ;i++){
        matrix_1[i]=1;
        matrix_2[i]=2;
        matrix_3[i]=0;
    } 
#pragma omp parallel for num_threads(numeroDeHilos) \
default(none) reduction(+:sum) shared(n,numeroDeHilos, matrix_1, matrix_2, matrix_3)
for(int i =0;i<numeroDeHilos;i++){
    sum_mat(matrix_1,matrix_2, matrix_3);
    for(int j=0;j<n;j++)
        printf("%d ", matrix_3[j]);
    printf("\n");
    }
}
void sum_mat(int * matrix_1, int *matrix_2, int * matrix_3)
{
    int my_rank = omp_get_thread_num();
    int numeroDeHilos = omp_get_num_threads();
    int ini = (n / numeroDeHilos) * my_rank;
    int fin = (n / numeroDeHilos) * my_rank + n / numeroDeHilos - 1;
    if (my_rank == numeroDeHilos-1)
        fin = n - 1;
        
    for (int i = ini; i < fin + 1; i++)
        matrix_3[i] = matrix_1[i] + matrix_2[i];
}