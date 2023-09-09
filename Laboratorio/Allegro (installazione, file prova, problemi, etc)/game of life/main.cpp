#include <allegro5/allegro.h>

#include "jallegro/Allegro.h"
#include "jallegro/Frame.h"
#include "GameOfLifePanel.h"

#include <iostream>
using namespace std;
using namespace jallegro;

int dim = 50;  // Dimensione della griglia
Panel* p;      // Puntatore a un oggetto Panel

// Dichiarazioni delle funzioni
bool analyzeMatrix(int, int, int**);
void game(int**, int**);
void print();

int main(int argc, char** argv) {
    Allegro::init();  // Inizializza Allegro

    srand(time(0));  // Inizializza il generatore di numeri casuali

    // Alloca memoria per due matrici bidimensionali di dimensione 'dim'
    int** mat1 = new int*[dim];
    int** mat2 = new int*[dim];

    // Inizializza mat1 con valori casuali (0 o 1)
    for (int i = 0; i < dim; ++i) {
        mat1[i] = new int[dim];
        mat2[i] = new int[dim];
        for (int j = 0; j < dim; ++j)
            mat1[i][j] = rand() % 2;
    }

    // Crea una finestra Allegro e un pannello per visualizzare il gioco
    Frame f(dim * 10 + 20, dim * 10 + 20, "Game of life");
    p = new GameOfLifePanel(mat1, dim, dim);
    f.add(p);
    f.show();

    // Avvia il gioco
    game(mat1, mat2);

    // Libera la memoria allocata
    for (int i = 0; i < dim; ++i) {
        delete[] mat1[i];
        delete[] mat2[i];
    }
    delete[] mat1;
    delete[] mat2;
    delete p;
    return 0;
}

// Implementazione della funzione 'game'
void game(int** mainMatrix, int** auxMatrix) {
    int time = 0;
    int time_limit = 1000;
    while (time < time_limit) {
        time++;
        print();  // Visualizza lo stato corrente
        Allegro::sleep(0.2);  // Pausa di 0.2 secondi

        // Calcola il prossimo stato del gioco
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                auxMatrix[i][j] = analyzeMatrix(i, j, mainMatrix);
            }
        }

        // Scambia mainMatrix e auxMatrix
        int** tmp = mainMatrix;
        mainMatrix = auxMatrix;
        auxMatrix = tmp;
    }
}

// Implementazione della funzione 'analyzeMatrix'
bool analyzeMatrix(int x, int y, int** mainMatrix) {
    int countAlive = 0;
    for (int i = x - 1; i <= x + 1; ++i) {
        for (int j = y - 1; j <= y + 1; ++j) {
            if (i >= 0 && i < dim && j >= 0 && j < dim) {
                if (mainMatrix[i][j] == 1)
                    countAlive++;
            }
        }
    }
    if (mainMatrix[x][y] == 1) {
        countAlive--;
        if (countAlive > 3 || countAlive < 2)
            return 0;  // La cella muore
        return 1;      // La cella sopravvive
    } else {
        if (countAlive == 3)
            return 1;  // Una nuova cella viene generata
        return 0;      // La cella rimane morta
    }
}

// Implementazione della funzione 'print'
void print() {
    p->repaint();  // Ridisegna il pannello di gioco
}
