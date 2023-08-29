#include <mpi.h>
#include <stdio.h>

void barrier(int rank, int size) {
    int dummy = 0;

    if(rank == 0){
        // Process 0 send the dummy message to other processes
        for (int dest = 1; dest < size; dest++){
            MPI_Send(&dummy, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
        }
        // Process 0 receive back the dummy message from other processes
        for (int src = 1; src < size; src++){
            MPI_Recv(&dummy, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }
    else{
        // Other Process receive the dummy message from Process 0
        MPI_Recv(&dummy, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        // Other Process send back the dummy message to other process
        MPI_Send(&dummy, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
}

int main(int argc, char *argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    printf("Process %d: Before Barrier\n", rank);
    barrier(rank, size);
    printf("Process %d: After Barrier\n", rank);

    MPI_Finalize();
    return 0;
}
