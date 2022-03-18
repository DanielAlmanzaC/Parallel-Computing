#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(){
int comm_sz; 
int my_rank; 

MPI_Init(NULL,NULL);
MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);
MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);

if(my_rank==0)
{
    int resultado=4;
    MPI_Send(&resultado,1,MPI_INT,1,0,MPI_COMM_WORLD);
    int total;
    MPI_Recv(&total,1,MPI_INT,3,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    printf("Con n = %d -> ((n*n)+2)*8 = %d\n", resultado, total);
}

else if(my_rank==1)
{
    int mi_variable;
    MPI_Recv(&mi_variable,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    int resultado=mi_variable*mi_variable;
    MPI_Send(&resultado,1,MPI_INT,2,0,MPI_COMM_WORLD);
}

else if(my_rank==2)
{
    int mi_variable;
    MPI_Recv(&mi_variable,1,MPI_INT,1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    int resultado=mi_variable+2;
    MPI_Send(&resultado,1,MPI_INT,3,0,MPI_COMM_WORLD);
}

else if(my_rank==3)
{
    int mi_variable;
    MPI_Recv(&mi_variable,1,MPI_INT,2,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    int resultado=mi_variable*8;
    MPI_Send(&resultado,1,MPI_INT,0,0,MPI_COMM_WORLD);
}

MPI_Finalize();
return 0;
}