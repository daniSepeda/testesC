#include <stdio.h>
#include "c:\msys64\ucrt64\include\ncurses\ncurses.h"
#include "elementos.c"
#include <unistd.h>
#include <stdlib.h>

#define HEIGHT 20
#define WIDTH 41

int main() {

    int gameOver = 0, i;

    initscr();
    cbreak();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);

    WINDOW * tela = newwin(HEIGHT, WIDTH, 5, 30); 
    box(tela, 0, 0);
    refresh(); //atualizar tudo dentro da borda

    player jogador = {tela, HEIGHT - 2, WIDTH / 2, HEIGHT, WIDTH, 1, '@'};
    player *pt = &jogador;

    shot * tiros[100]; //um vetor de ponteiros do tipo shot
    
    for (int i = 0; i < 100; i++) {
        tiros[i] = (shot*)malloc(sizeof(shot));
        *(tiros[i]) = newShot(tela, 0, 0, 0, '^');
    }

    //shot tiro = {tela, jogador.yAtual - 1, jogador.xAtual, 0, '^'};
    //shot *ptiro = &tiro;

    while (!gameOver) {

        mover(pt, tiros[100]);          // mover jogador e receber ação
        moverTiro(tiros[100]);          // mover tiro
        atualizar(pt, tiros[100]);      // atualizar elementos na tela
        usleep(100000);            // delay para o movimento do tiro em microsegundos, nesse caso, de 0.1s
    }

    getch();

    endwin();

    return 0;
}

