#include "c:\msys64\ucrt64\include\ncurses\ncurses.h"
#include "elementos.h"
#include <unistd.h>

// função para receber e atribuir valores a uma variavel do tipo player
player newPlayer(WINDOW *winAtual, int yAtual, int xAtual, int yMax, int xMax, int lifes, char format) {
     player tempPlayer = {winAtual, yAtual, xAtual, yMax, xMax, lifes, format};
     return tempPlayer;
}

// função para receber e atribuir valores a uma variavel do tipo shot
shot newShot(WINDOW *winAtual, int yAtual, int xAtual, int lancado, char format) {
     shot tempShot = {winAtual, yAtual, xAtual, lancado, format};
     return tempShot;
}

//ações do jogador em geral
void mover(player * Jogador, shot *tiros[100]) {
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
            //shot * tiros[i] = tiro;

            for (int i = 0; i < 100; i++) {
                if (tiros[i]->lancado == 0) {
                    tiros[i]->lancado = 1;
                    tiros[i]->yAtual = Jogador->yAtual - 1;
                    tiros[i]->xAtual = Jogador->xAtual;
                    break;
                } 
            }
            break;
        default:
            break;
    }

}

// atualizar coordenadas do jogador
void atualizar(player * Jogador, shot* tiros[100]) {
    mvwaddch(Jogador->winAtual, Jogador->yAtual, Jogador->xAtual, '@');
    wrefresh(Jogador->winAtual);

    //shot *tiros[i] = tiro;

    for (int i = 0; i < 100; i++) {
        if (tiros[i]->lancado == 1) {
            mvwaddch(tiros[i]->winAtual, tiros[i]->yAtual, tiros[i]->xAtual, tiros[i]->format);
            wrefresh(tiros[i]->winAtual);
        }
    }
}

void moverTiro(shot *tiros[100]) {
    //shot *tiros[i] = tiro;

    for (int i = 0; i < 100; i++) {
        if (tiros[i]->lancado == 1) {
            if (tiros[i]->yAtual > 1) {
                mvwaddch(tiros[i]->winAtual, tiros[i]->yAtual, tiros[i]->xAtual, ' ');
                wrefresh(tiros[i]->winAtual);
                tiros[i]->yAtual--;
                //tiro ainda nao chegou na altura final
            } else {
                mvwaddch(tiros[i]->winAtual, tiros[i]->yAtual, tiros[i]->xAtual, ' ');
                //tiros[i]->format = ' ';
                tiros[i]->lancado = 0;
                //tiro chegou na altura final
            }
        }
    }
}
