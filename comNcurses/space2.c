#include <stdio.h>
#include "c:\msys64\ucrt64\include\ncurses\ncurses.h"
#include <unistd.h>
#include <stdlib.h>

#define HEIGHT 20
#define WIDTH 41

typedef struct player {
    WINDOW *win;
    int y;
    int x;
    int lifes;
    char format;
}player;

typedef struct shot {
    WINDOW *win;
    int y;
    int x;
    int lancado;
    char format;
}shot;

player jogador;
shot tiros[100];

player newPlayer(WINDOW *win, int y, int x, int lifes, char format);

shot newShot(WINDOW *win, int y, int x, int lancado, char format);

void mover( void );

void atualizar( void );

void moverTiro( void );

int main() {

    int gameOver = 0, i;

    initscr();
    cbreak();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);

    WINDOW * tela = newwin(HEIGHT, WIDTH, 5, 30); 
    box(tela, 0, 0);
    refresh(); // atualizar tudo dentro da borda

    jogador = newPlayer(tela, HEIGHT - 2, WIDTH / 2, 1, '@');

    for (int i = 0; i < 100; i++) {
        tiros[i] = newShot(tela, 0, 0, 0, '^');
    }

    while (!gameOver) {
        mover();
        moverTiro();
        atualizar();
        usleep(100000); //microssegundo
    }
    getch();

    endwin();

    return 0;

}

player newPlayer(WINDOW *win, int y, int x, int lifes, char format) {
    player temp = {win, y, x, lifes, format};
    return temp;
}

shot newShot(WINDOW *win, int y, int x, int lancado, char format) {
    shot temp = {win, y, x, lancado, format};
    return temp;
}

void mover (void) {
    int valor;
    valor = getch();

    switch(valor) {
        case (97):
            mvwaddch(jogador.win, jogador.y, jogador.x, ' ');
            if (jogador.x > 1) {
                jogador.x--;
            } 
            break;
        case (100):
            mvwaddch(jogador.win, jogador.y, jogador.x, ' ');
            if (jogador.x < WIDTH - 2) {
                jogador.x++;
            }
            break;
        case (119):
            for (int i = 0; i < 100; i++) {
                if (tiros[i].lancado == 0) {
                    tiros[i].lancado = 1;
                    tiros[i].y = jogador.y - 1;
                    tiros[i].x = jogador.x;
                    break;
                } 
            }
            break;
        default:
            break;
    }
}

void moverTiro(void) {
    for (int i = 0; i < 50; i++) {
        if (tiros[i].lancado == 1) {

            mvwaddch(tiros[i].win, tiros[i].y, tiros[i].x, ' ');
            wrefresh(tiros[i].win);

            if (tiros[i].y > 1) {
                tiros[i].y--;
            } else {
               tiros[i].lancado = 0;
            }
        }
    }
    
}

void atualizar (void) {
    mvwaddch(jogador.win, jogador.y, jogador.x, jogador.format);
    wrefresh(jogador.win);

    for (int i = 0; i < 50; i++) {
        if (tiros[i].lancado == 1) {
            mvwaddch(tiros[i].win, tiros[i].y, tiros[i].x, tiros[i].format);
            wrefresh(tiros[i].win);
        }
    }

}
