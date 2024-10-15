#include <stdio.h>
#include "c:\msys64\ucrt64\include\ncurses\ncurses.h"
#include "elementos.c"
#include <unistd.h>

#define HEIGHT 20
#define WIDTH 41

int main() {

    int gameOver = 0, tiros, tiro_chegada = 1;

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

    shot tiro = {tela, jogador.yAtual - 1, jogador.xAtual, 0, '^'};
    shot *ptiro = &tiro;

    while (!gameOver) {

        mover(pt, ptiro);          // mover jogador e receber ação
        moverTiro(ptiro);          // mover tiro
        atualizar(pt, ptiro);      // atualizar elementos na tela
        usleep(100000);            // delay para o movimento do tiro em microsegundos, nesse caso, de 0.1s
    }

    getch();

    endwin();

    return 0;
}

