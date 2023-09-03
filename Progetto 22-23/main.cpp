#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <mpi.h>
#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <random>
#include <time.h>
#include <string>

int* readM;
int* writeM;

void transitionFunction(int x, int y){
    int cont = 0;
    // Conto i vicini vivi
    for(int di = -1; di < 2; di++)
        for(int dj = -1; dj < 2; dj++)
            if ((di!=0 || dj!=0) && readM[v((i+di+NROWS)%NROWS,(j+dj+NCOLS)%NCOLS)] == 1)
                cont++;

    // Regole Gioco della Vita
    if (readM[v(i,j)] == 1)
        if (cont == 2 || cont == 3)
            writeM[v(i,j)]=1;
        else
            writeM[v(i,j)]=0;
    else
        if (cont == 3)
            writeM[v(i,j)]=1;
        else
            writeM[v(i,j)]=0;
};

int main(int argc, char *argv[]) {
    readM = new int[(NROW/NPROC+2)*NCOLS];
    writeM = new int[(NROW/NPROC+2)*NCOLS];
}