#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define maxsize 3000  // Dimensione massima del buffer

MPI_Request req;      // Richiesta per l'invio o la ricezione asincrona
MPI_Status status;    // Stato dell'operazione MPI
int cont, buffer[maxsize];  // Variabile contatore e buffer per l'invio/ricezione dei dati

// Funzione per la barriera personalizzata
void barrier(int rank, int size) {
    cont++;
    
    // Invia token a tutti gli altri processi
    for (int dest = 0; dest < size; dest++) {
        if (dest != rank) {
            MPI_Isend(&buffer[0], size, MPI_INT, dest, cont, MPI_COMM_WORLD, &req);  // Invia dati asincronamente
            MPI_Wait(&req, &status);  // Attendi completamento dell'invio
        }
    }

    // Ricevi token da tutti gli altri processi
    for (int src = 0; src < size; src++) {
        if (src != rank) {
            MPI_Irecv(&buffer[0], size, MPI_INT, src, cont, MPI_COMM_WORLD, &req);  // Ricevi dati asincronamente
            MPI_Wait(&req, &status);  // Attendi completamento della ricezione
        }
    }
}

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Ottieni il numero totale di processi
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Ottieni il rank (ID) del processo
    
    // Ciclo per la stampa "Before Barrier"
    for (int i = 0; i < size; i++) {
        if (rank == i) {
            printf("Process %d: Before Barrier\n", rank);
            fflush(stdout);  // Assicura la stampa immediata
        }
        barrier(rank, size);  // Chiamata alla barriera personalizzata
    }
    
    // Ciclo per la stampa "After Barrier"
    for (int i = 0; i < size; i++) {
        barrier(rank, size);  // Chiamata alla barriera personalizzata
        if (rank == i) {
            printf("Process %d: After Barrier\n", rank);
            fflush(stdout);  // Assicura la stampa immediata
        }
    }
    
    MPI_Finalize();  // Finalizza MPI
    return 0;
}
