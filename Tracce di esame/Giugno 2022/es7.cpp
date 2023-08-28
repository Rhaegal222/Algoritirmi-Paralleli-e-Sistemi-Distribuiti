#include "mpich/mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define maxsize 3000

MPI_Request req;
MPI_Status status;
int cont, buffer[maxsize];

void barrier(int rank, int size) {
    cont++;
    
    // Invia token a tutti gli altri processi
    for (int dest = 0; dest < size; dest++) {
        if (dest != rank) {
            MPI_Isend(&buffer[0], size, MPI_INT, dest, cont, MPI_COMM_WORLD, &req);
        }
    }
    
    // Ricevi token da tutti gli altri processi
    for (int src = 0; src < size; src++) {
        if (src != rank) {
            MPI_Recv(&buffer[0], size, MPI_INT, src, cont, MPI_COMM_WORLD, &status);
        }
    }
}

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    // Chiamata alla barriera personalizzata
    barrier(rank, size);
    
    MPI_Finalize();
    return 0;
}
