#include <stdio.h>
#include <string.h>
#include <mpi.h>


//mpicc -std=c99 -o archivoDeSDalida 001ProgramaDeMPI.c 
//mpiexec -n 4 ./archivoDeSDalida.exe

const int MAX_STRING=50;

int main(void){

	char saludos[MAX_STRING];
	int comm_sz; //numero de procesos
	int my_rank; //nombre del proceso
	
	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
	
	
	if(my_rank!=0){
		sprintf(saludos,"Saludos del proceso %d de %d!",my_rank,comm_sz);
		MPI_Send(saludos,strlen(saludos)+1,MPI_CHAR,0,0,MPI_COMM_WORLD);
		
	}else{
	
		printf("Saludos del proceso %d de %d!\n",my_rank,comm_sz);
		for(int q=1;q<comm_sz;q++){
			MPI_Recv(saludos,MAX_STRING,MPI_CHAR,q,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			printf("%s\n",saludos);
		}
	}

	MPI_Finalize();
	return 0;
}

