#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    
    MPI_Init(&argc, &argv);   // Inizializza MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Ottiene il rank (ID) del processo
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Ottiene il numero totale di processi
    
    printf("Process %d: Before Barrier\n", rank);
    
    MPI_Barrier(MPI_COMM_WORLD);  // Barriera: tutti i processi attendono qui
    
    printf("Process %d: After Barrier\n", rank);
    
    MPI_Finalize();  // Finalizza MPI
    
    return 0;
}
