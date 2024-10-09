#include <stdio.h>
#include "c:\msys64\ucrt64\include\ncursesw\ncurses.h"
#include "player.c"

#define HEIGHT 20
#define WIDTH 41

int main() {

    int gameOver = 0;

    initscr();
    cbreak;
    //noecho();
    curs_set(0);

    WINDOW * tela = newwin(HEIGHT, WIDTH, 5, 30); //atualizar tudo dentro da borda
    box(tela, 0, 0);
    refresh();

    player jogador = newPlayer(tela, HEIGHT - 2, WIDTH / 2, HEIGHT, WIDTH, 1, '@');

    player * pt = &jogador;
    while (!gameOver) {
        mostrar(pt);
        mover(pt);
    }

    getch();

    endwin();

    return 0;
}