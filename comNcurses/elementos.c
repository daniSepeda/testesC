#include "c:\msys64\ucrt64\include\ncursesw\ncurses.h"
#include "elementos.h"
#include <unistd.h>

// função para receber e atribuir valores a uma variavel do tipo player
player newPlayer(WINDOW *winAtual, int yAtual, int xAtual, int yMax, int xMax, int lifes, char format) {
     player tempPlayer = {winAtual, yAtual, xAtual, yMax, xMax, lifes, format};
     return tempPlayer;
}

// move para a direita se o jogador nao atingiu a borda
void moverDireita(player * Jogador){
    mvwaddch(Jogador->winAtual, Jogador->yAtual, Jogador->xAtual, ' ');
    if (Jogador->xAtual < Jogador->xMax - 2) {
        Jogador->xAtual++;
    } else {
        Jogador->xAtual = Jogador->xMax - 2;
    }
}

//move para a esquerda se o jogador não atingiu a borda
void moverEsquerda(player * Jogador) {
    mvwaddch(Jogador->winAtual, Jogador->yAtual, Jogador->xAtual, ' ');
    if (Jogador->xAtual > 1) {
        Jogador->xAtual--;
    } else {
        Jogador->xAtual = 1;
    }
}

//move o jogador em geral
void mover(player * Jogador, shot *tiro) {
    int valor;
    valor = getch();

    switch(valor) {
        case (97):
            moverEsquerda(Jogador);
            break;
        case (100):
            moverDireita(Jogador);
            break;
        case (119):
            atirar(tiro);
            break;
        default:
            break;
    }

}

// atualizar coordenadas do jogador
void atualizar(player * Jogador, shot*tiro) {
    mvwaddch(Jogador->winAtual, Jogador->yAtual, Jogador->xAtual, '@');
    wrefresh(Jogador->winAtual);

    if (tiro->lancado == 1) {
    mvwaddch(tiro->winAtual, tiro->yAtual, tiro->xAtual, tiro->format);
    wrefresh(tiro->winAtual);
    }
}

void atirar(shot *tiro) {
    tiro->lancado = 1;
    if (tiro->yAtual > 1) {
        mvwaddch(tiro->winAtual, tiro->yAtual, tiro->xAtual, ' ');
        wrefresh(tiro->winAtual);
        tiro->yAtual--;
        usleep(10000); // tempo em microsegundos
    //tiro ainda nao chegou no final
    } else {
        tiro->format = ' ';
         //tiro chegou no final
    }
}
