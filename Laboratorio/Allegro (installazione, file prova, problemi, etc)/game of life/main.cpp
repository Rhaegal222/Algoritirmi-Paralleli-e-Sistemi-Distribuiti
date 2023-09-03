#include <allegro5/allegro.h>

#include "jallegro/Allegro.h"
#include "jallegro/Frame.h"
#include "GameOfLifePanel.h"

#include <iostream>
using namespace std;
using namespace jallegro;

int dim=50;
Panel* p;

bool analyzeMatrix(int, int, int** );
void game(int**,int**);
void print();

int main(int argc, char **argv) {
    Allegro::init();

    srand(time(0));
    int **mat1 = new int* [dim];
    int **mat2 = new int* [dim];

    for (int i=0;i<dim;++i) {
        mat1[i] = new int[dim];
        mat2[i] = new int[dim];
        for (int j=0;j<dim;++j)
            mat1[i][j]=rand()%2;
    }

    //Code for showing a window and a panel
    Frame f(dim * 10 + 20, dim * 10 + 20, "Game of life");
    p = new GameOfLifePanel(mat1, dim, dim);
    f.add(p);
    f.show();
    game(mat1, mat2);

    for (int i=0;i<dim;++i) {
        delete[] mat1[i];
        delete[] mat2[i];
    }
    delete[] mat1;
    delete[] mat2;
    delete p;
    return 0;
}

void game(int** mainMatrix, int** auxMatrix) {
    int time = 0;
    int time_limit = 1000;
    while(time < time_limit) {
        time++;
        print();
        Allegro::sleep(0.2);
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                auxMatrix[i][j] = analyzeMatrix(i, j, mainMatrix);
            }
        }
        //Swap mainMatrix and auxMatrix
        int** tmp = mainMatrix;
        mainMatrix = auxMatrix;
        auxMatrix = tmp;
    }
}

bool analyzeMatrix(int x, int y, int** mainMatrix) {
    int countAlive = 0;
    for (int i=x-1;i<=x+1;++i) {
        for (int j=y-1;j<=y+1;++j) {
            if (i>=0 && i<dim && j>=0 && j<dim) {
                if (mainMatrix[i][j] == 1)
                    countAlive++;
            }
        }
    }
    if (mainMatrix[x][y] == 1) {
        countAlive--;
        if (countAlive > 3 || countAlive < 2)
            return 0;
        return 1;
    }
    else  {
        if (countAlive == 3)
            return 1;
        return 0;
    }
}

void print() {
    p->repaint();
}