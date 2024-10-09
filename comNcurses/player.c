#include "c:\msys64\ucrt64\include\ncursesw\ncurses.h"
#include "player.h"


player newPlayer(WINDOW *winAtual, int yAtual, int xAtual, int yMax, int xMax, int lifes, char format) {
     player tempPlayer = {winAtual, yAtual, xAtual, yMax, xMax, lifes, format};
     return tempPlayer;
}

void moverDireita(player * Jogador){
    mvwaddch(Jogador->winAtual, Jogador->yAtual, Jogador->xAtual, ' ');
    if (Jogador->xAtual < Jogador->xMax - 2) {
        Jogador->xAtual++;
    } else {
        Jogador->xAtual = Jogador->xMax - 2;
    }
}

void moverEsquerda(player * Jogador) {
    mvwaddch(Jogador->winAtual, Jogador->yAtual, Jogador->xAtual, ' ');
    if (Jogador->xAtual > 1) {
        Jogador->xAtual--;
    } else {
        Jogador->xAtual = 1;
    }
}

void mover(player * Jogador) {
    int valor;

    valor = getch();

    switch(valor) {
        case (97):
            moverEsquerda(Jogador);
            break;
        case (100):
            moverDireita(Jogador);
            break;
        default:
            break;
    }
}

void mostrar(player * Jogador) {
    mvwaddch(Jogador->winAtual, Jogador->yAtual, Jogador->xAtual, '@');
    wrefresh(Jogador->winAtual);
}
