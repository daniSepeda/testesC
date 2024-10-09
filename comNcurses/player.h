#ifndef PLAYER
#define PLAYER

#include "c:\msys64\ucrt64\include\ncursesw\ncurses.h"

typedef struct player {
    WINDOW * winAtual;
    int yAtual;
    int xAtual;
    int yMax;
    int xMax;
    int lifes;
    char format;
}player;

player newPlayer(WINDOW *win, int yAtual, int xAtual, int yMax, int xMax, int lifes, char format);

void moverDireita(player * Jogador);

void moverEsquerda(player * Jogador);

void mover(player * Jogador);

void mostrar(player *Jogador);

#endif //PLAYER