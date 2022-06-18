#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<time.h>

static int *a;
static int *index;
int n=2000000;

static int compara(const void *a,const void *b);
static void qs(int *a,int n, int *index,int num);
void reemplazo(int *A,int *B, int n1,int n2);

int main(int argc, char*argv[])
{
    int i;
    double inicio = omp_get_wtime();
    a = (int*)malloc(n*sizeof(int));
    srand(time(NULL));
    for (int i=0;i<n;i++)
    {
        a[i] = (int)rand()%n;
    }

    int numeroDeHilos=strtol(argv[1],NULL,10);
	omp_set_num_threads(numeroDeHilos);
	index = (int *)malloc((numeroDeHilos+1)*sizeof(int));
    #pragma omp parallel for num_threads(numeroDeHilos) private(i)
	for(i=0;i<numeroDeHilos;i++) 
    {
		index[i]=i*n/numeroDeHilos;           
		index[numeroDeHilos]=n;  
    }

    //Aquí se imprime el arreglo desordenado, lo quité xq cuando son muchos números ni se puede ver xd
    //for (i=0;i<n;i++)
    //  printf("%d ",a[i]);
    //printf("\n");

	#pragma omp parallel for num_threads(numeroDeHilos) private(i)
	for(i=0;i<numeroDeHilos;i++) 
		qsort(a+index[i], index[i+1]-index[i], sizeof(int),compara); //La función de qsort sirve para particionar el arreglo para que luego pueda ordenarse correctamente

    for (i=0;i<n;i++)
    {
        printf("%d ",a[i]);
    }
	
	if( numeroDeHilos>1) 
		qs(a, n, index, numeroDeHilos);

    double final = omp_get_wtime();
    double dif = final-inicio;
    printf("Ordenado: \n");
    for (i=0;i<n;i++)
        printf("%d ",a[i]);

    printf("\nEl tiempo utilizado fue de: %f segundos uwu\n",dif);
    free(index);
    free(a);
}

static int compara(const void *a, const void *b) //Esta función le indica a qsort el cómo será la ordenación, ya sea de mayor a menor o viceversa
{
	return (*(int*)a-*(int*)b);
}

static void qs(int *a, int n, int *index, int num)
{
	int i;
	while (num>1) 
    {	    
        #pragma omp for
		for(i=0;i<num;i++)
			index[i] = i*n/num;             
		index[num]=n;                       
		
		#pragma omp for
	    for(i=0;i<num;i=i+2)
			reemplazo(a+index[i], a+index[i+1], index[i+1]-index[i], index[i+2]-index[i+1]);				
	    num = num/2;
	}
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