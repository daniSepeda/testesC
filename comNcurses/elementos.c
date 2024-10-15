#include "c:\msys64\ucrt64\include\ncurses\ncurses.h"
#include "elementos.h"
#include <unistd.h>

// função para receber e atribuir valores a uma variavel do tipo player
player newPlayer(WINDOW *winAtual, int yAtual, int xAtual, int yMax, int xMax, int lifes, char format) {
     player tempPlayer = {winAtual, yAtual, xAtual, yMax, xMax, lifes, format};
     return tempPlayer;
}

//ações do jogador em geral
void mover(player * Jogador, shot *tiro) {
    int valor;
    valor = getch();

    switch(valor) {
        case (97):
            mvwaddch(Jogador->winAtual, Jogador->yAtual, Jogador->xAtual, ' ');
            if (Jogador->xAtual > 1) {
                Jogador->xAtual--;
            } 
            break;
        case (100):
            mvwaddch(Jogador->winAtual, Jogador->yAtual, Jogador->xAtual, ' ');
            if (Jogador->xAtual < Jogador->xMax - 2) {
                Jogador->xAtual++;
            }
            break;
        case (119):
            tiro->lancado = 1;
            tiro->yAtual = Jogador->yAtual - 1;
            tiro->xAtual = Jogador->xAtual;
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
    //usleep(100000); // tempo em microsegundos
    }
}

void moverTiro(shot *tiro) {
    if (tiro -> lancado == 1) {
        if (tiro->yAtual > 1) {
            mvwaddch(tiro->winAtual, tiro->yAtual, tiro->xAtual, ' ');
            wrefresh(tiro->winAtual);
            tiro->yAtual--;
        //tiro ainda nao chegou no final
        } else {
            mvwaddch(tiro->winAtual, tiro->yAtual, tiro->xAtual, ' ');
            tiro->format = ' ';
            tiro->lancado = 0;
            //tiro chegou no final
        }
    }
}
