#ifndef JALLEGRO_MYPANEL_H
#define JALLEGRO_MYPANEL_H

#include "jallegro/Panel.h"
using namespace jallegro;

class GameOfLifePanel : public Panel {

    public:
        GameOfLifePanel(int** world, int n, int m) {
            this->world = world;
            this->n = n;
            this->m = m;
        }

    protected:
        void paintComponent(Graphics g) {
            Panel::paintComponent(g);
            int blockSize = 10;
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < m; j++) {
                    if (world[i][j] == 0)
                        g.setColor(Color::white());
                    else
                        g.setColor(Color::black());
                    g.fillRect(10+i*blockSize, 10+ j*blockSize, blockSize, blockSize);
                }
            }
        }

    private:
        int** world;
        int n;
        int m;
};

#endif