#include <stdio.h>
#include "c:\msys64\ucrt64\include\ncursesw\ncurses.h"

#define SIZE_X 17 //linhas
#define SIZE_Y 27 //colunas

typedef struct player {
    char format; //formato
    int lifes;  // quantidade de vidas
    int x, y;   // coordenadas dentro da matriz
}player;

player Jogador = {'H', 1, SIZE_X - 2, SIZE_Y / 2}; 

//preencher a tela
void fillScreen(char screen[][SIZE_Y]){
    int i, j;
    for (i = 0; i < SIZE_X; i++) {
        for (j = 0; j < SIZE_Y; j++) {
            if (i == 0 || j == 0 || j == SIZE_Y - 1 || i == SIZE_X -1) {
                screen[i][j] = '*';
            } else {
                screen[i][j] = ' ';
            }
        }
    }

    // o jogador é colocado nas suas coordenadas
    screen[Jogador.x][Jogador.y] = Jogador.format;
}

void printScreen(char screen[][SIZE_Y]) {
     int i, j;
     clear(); // limpar a tela antes de desenhar novamente
     for (i = 0; i < SIZE_X; i++) {
        for (j = 0; j < SIZE_Y; j++) {
            printw("%c", screen[i][j]);
        }
        printw("\n");
    }
    refresh();
}


void movePlayer() {
    int value;

    value = getch();

    switch (value) {
        case (97):  // tecla 'a' para mover para a esquerda
            if (Jogador.y > 1) {
                Jogador.y--;
            }
            break;
        case (100): // tecla 'd' para mover para a direita
            if (Jogador.y < SIZE_Y - 2) {
                Jogador.y++;
            }
            break;
    }
}

int main() {

    char tela[SIZE_X][SIZE_Y];
    int gameover = 0;

    initscr();
    noecho();
    cbreak();
    curs_set(0); // ocultar o cursor

    while (!gameover) {
        fillScreen(tela);
        printScreen(tela);
        movePlayer();
    }

    endwin();
    return 0;
}
