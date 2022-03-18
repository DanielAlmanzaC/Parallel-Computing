#include <stdio.h>
#include <string.h>
#include <mpi.h>

const int MAX_STRING=50;

int main(void){

    int comm_sz; //numero de procesos
    int my_rank; //nombre del proceso

    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);

    if(my_rank==0){ 
        int resultado=10;
        MPI_Send(&resultado,1,MPI_INT,1,0,MPI_COMM_WORLD); 
        MPI_Send(&resultado,1,MPI_INT,2,0,MPI_COMM_WORLD); 
        MPI_Send(&resultado,1,MPI_INT,3,0,MPI_COMM_WORLD); 
        int r1,r2,r3;
        MPI_Recv(&r1,1,MPI_INT,1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        MPI_Recv(&r2,1,MPI_INT,2,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        MPI_Recv(&r3,1,MPI_INT,3,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("n   = %d\nn^2 = %d\nn+n = %d\nn+2 = %d\n", resultado,r1,r2,r3);
    }
    else if(my_rank==1){
        int mi_variable;
        MPI_Recv(&mi_variable,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        int resultado=mi_variable*mi_variable;
        MPI_Send(&resultado,1,MPI_INT,0,0,MPI_COMM_WORLD);  
    }
    else if(my_rank==2){
        int mi_variable;
        MPI_Recv(&mi_variable,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        int resultado=mi_variable+mi_variable;
        MPI_Send(&resultado,1,MPI_INT,0,0,MPI_COMM_WORLD);  
    }
    else if(my_rank==3){
        int mi_variable;
        MPI_Recv(&mi_variable,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        int resultado=mi_variable+2;
        MPI_Send(&resultado,1,MPI_INT,0,0,MPI_COMM_WORLD);  
    }
    
    MPI_Finalize();
    return 0;
}