#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    
    MPI_Init(&argc, &argv);   // Inizializza MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Ottiene il rank (ID) del processo
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Ottiene il numero totale di processi
    
    for (int i = 0; i < size; i++) {
        if (rank == i) {
            printf("Process %d: Before Barrier\n", rank);
            fflush(stdout);
        }
        MPI_Barrier(MPI_COMM_WORLD);  // Barriera: tutti i processi attendono qui
    }
    
    for (int i = 0; i < size; i++) {
        MPI_Barrier(MPI_COMM_WORLD);  // Barriera: tutti i processi attendono qui
        if (rank == i) {
            printf("Process %d: After Barrier\n", rank);
            fflush(stdout);
        }
    }
    
    MPI_Finalize();  // Finalizza MPI
    
    return 0;
}
