#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<time.h>
// gcc -g -Wall -o QSPthreads QuickSortPThreads.c -lpthread -lm
// ./QSPthreads 4

static int *a;
static int *index;
int n=2000000;
int numeroDeHilos;

static int compara(const void *a,const void *b);
//static void qs(int *a,int n, int *index,int num);
void * qs(void *rank);
void reemplazo(int *A,int *B, int n1,int n2);

int main(int argc, char*argv[])
{
    int i;
    clock_t start;
    long my_rank;
    pthread_t *manejadorDeHilos;
    numeroDeHilos=strtol(argv[1],NULL,10);
    manejadorDeHilos=malloc(numeroDeHilos*sizeof(pthread_t));

    start=clock();

    a = (int*)malloc(n*sizeof(int));
    srand(time(NULL));
    for (int i=0;i<n;i++)
    {
        a[i] = (int)rand()%n;
    }

    index = (int *)malloc((numeroDeHilos+1)*sizeof(int));
	for(i=0;i<numeroDeHilos;i++) 
    {
	    index[i]=i*n/numeroDeHilos;           
	    index[numeroDeHilos]=n;  
    }

    for(i=0;i<numeroDeHilos;i++) 
		qsort(a+index[i], index[i+1]-index[i], sizeof(int),compara); //La función de qsort sirve para particionar el arreglo para que luego pueda ordenarse correctamente
	
    for (my_rank = 0; my_rank < numeroDeHilos; my_rank++)
	    pthread_create(&manejadorDeHilos[my_rank],NULL,qs,(void*)my_rank);
	
	for (my_rank = 0; my_rank < numeroDeHilos; my_rank++)
        pthread_join(manejadorDeHilos[my_rank],NULL);

    printf("\nArreglo ordenado \n");
    for (i=0;i<n;i++)
    {
        printf("%d ",a[i]);
    }

    printf("\nTiempo de ejecución: %.4f s\n", (double)(clock() - start) / CLOCKS_PER_SEC);


    free(index);
    free(a);
}

static int compara(const void *a, const void *b) //Esta función le indica a qsort el cómo será la ordenación, ya sea de mayor a menor o viceversa
{
	return (*(int*)a-*(int*)b);
}

void * qs(void *rank)
{
    long my_rank=(long)rank;
	int i;
	while (numeroDeHilos>1) 
    {	    
		for(i=0;i<numeroDeHilos;i++)
			index[i] = i*n/numeroDeHilos;             
		index[numeroDeHilos]=n;                       
		
	    for(i=0;i<numeroDeHilos;i=i+2)
			reemplazo(a+index[i], a+index[i+1], index[i+1]-index[i], index[i+2]-index[i+1]);				
	    numeroDeHilos = numeroDeHilos/2;
	}

    //printf("\nOrdenación %ld\n",my_rank);
    //for (i=0;i<n;i++)
    //{
      //  printf("%d ",a[i]);
    //}
}

void reemplazo(int *A, int *B, int n1, int n2) 
{
	int i = 0, j = 0, k = 0,t;
	int n = n1 + n2;
	int *aux = (int *)malloc(n * sizeof(int));
	
	while (i<n1 && j<n2) 
    {
		if (A[i] <= B[j]) 
			aux[k] = A[i++];
		else aux[k] = B[j++];
		k++;
	}
	
	if (i<n1) 
    {                           
		for (t=i;t<n1;t++,k++) 
			aux[k] = A[t];
	}
	else 
    {                                     
		for (t=j;t<n2;t++,k++)   
			aux[k] = B[t];
	}
	
	for(i=0;i<n;i++)    
		A[i] = aux[i];
	
	free(aux);
}