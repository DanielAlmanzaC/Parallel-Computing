#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
int i,j,aux,n=200000;
int main(int argc, char*argv[])
{
    // gcc -g -Wall -fopenmp -o OddEven OddEven.c -lm
    // ./OddEven 4
    int a[n];
    double inicio = omp_get_wtime();
    srand(time(NULL));
    for (int i=0;i<n;i++)
        a[i] = (int)rand()%n;

    int numeroDeHilos=strtol(argv[1],NULL,10);
    #pragma omp parallel num_threads(numeroDeHilos) \
        default(none) shared(a,n) private(j,aux)
    for(int i=0;i<n;i++)
    {
        if(i%2==0)
        {
        #pragma omp for
            for(j=1;j<n;j+=2)
            {
                if(a[j-1]>a[j])
                {
                        aux=a[j];
                        a[j]=a[j-1];
                        a[j-1]=aux;
                }
            }
        }
        else
        {
        #pragma omp for
            for(j=1;j<n-1;j+=2)
            {
                if(a[j]>a[j+1])
                {
                        aux=a[j];
                        a[j]=a[j+1];
                        a[j+1]=aux;
                }
            }
        }
    }
    double final = omp_get_wtime();
    double dif = final-inicio;
    printf("\nEl arreglo ordenado es el siguiente: \n");
    for(i=0;i<n;i++)
    {
        printf("%d ",a[i]);
    }
    printf("\nEl tiempo utilizado fue de: %f segundos uwu\n",dif);
}