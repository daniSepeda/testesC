#include <stdio.h>
#include "c:\msys64\ucrt64\include\ncursesw\ncurses.h"
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

    WINDOW * tela = newwin(HEIGHT, WIDTH, 5, 30); //atualizar tudo dentro da borda
    box(tela, 0, 0);
    refresh();


    player jogador = newPlayer(tela, HEIGHT - 2, WIDTH / 2, HEIGHT, WIDTH, 1, '@');
    player *pt = &jogador;

    shot tiro = {tela, jogador.yAtual - 1, jogador.xAtual, 0, '^'};
    shot *ptiro = &tiro;

    while (!gameOver) {

        atualizar(pt, ptiro);
        mover(pt, ptiro);

    }

    getch();

    endwin();

    return 0;
}

