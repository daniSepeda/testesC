#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define SCREEN_SIZE_Y 13 //linhas - desconsiderando as bordas são 11 linhas 
#define SCREEN_SIZE_X 23 //colunas - desconsiderando as bordas são 21 colunas

typedef struct player {
    char format; //formato
    int lifes;  // quantidade de vidas
    int x, y;   // coordenadas dentro da matriz
}player;

typedef struct shot {
    char format;
    int visibility;
    int y;
    int x;
}shot;

void fillScreen(char screen[][SCREEN_SIZE_X]);

void printScreen(char screen[][SCREEN_SIZE_X]);

void movePlayer(char screen[][SCREEN_SIZE_X]);

void playerShot();

player Jogador = {'@', 1, SCREEN_SIZE_Y - 2, SCREEN_SIZE_X / 2}; 

int main() {

    char tela[SCREEN_SIZE_Y][SCREEN_SIZE_X];
    int gameOver = 0; // falso

    fillScreen(tela);
    printScreen(tela);

    while (!gameOver) {
        movePlayer(tela);
    }

    return 0;
}

//preencher a tela
void fillScreen(char screen[][SCREEN_SIZE_X]){
    int i, j;
    for (i = 0; i < SCREEN_SIZE_Y; i++) {
        for (j = 0; j < SCREEN_SIZE_X; j++) {
            if (i == 0 || j == 0 || j == SCREEN_SIZE_X - 1 || i == SCREEN_SIZE_Y -1) {
                screen[i][j] = '*';
            } else {
                screen[i][j] = ' ';
            }
        }
    }

    // o jogador é colocado nas suas coordenadas
    screen[Jogador.x][Jogador.y] = Jogador.format;
}

//printar tela
void printScreen(char screen[][SCREEN_SIZE_X]) {
     int i, j;
     for (i = 0; i < SCREEN_SIZE_Y; i++) {
        for (j = 0; j < SCREEN_SIZE_X; j++) {
            printf("%c", screen[i][j]);
        }
        printf("\n");
    }
}

//mover jogador
void movePlayer(char screen[][SCREEN_SIZE_X]) {
    int check = 1;  //flag para checar se a teclas certas foram apertadas
    int value;

    do {
        value = getch();

        switch (value) {
            case (97):
                if (Jogador.y > 1) {
                    Jogador.y--;
                    check = 0;
                }
                break;
            case (100):
                if (Jogador.y < SCREEN_SIZE_X - 2) {
                    Jogador.y++;
                    check = 0;
                }
                break;

        //getchar(); // pega o caractere de quebra de linha se tiver
        }

    } while (check);

    system("cls");
    fillScreen(screen);
    printScreen(screen);

}

void playerShot( void ) {
    shot tiro = {'I', 1, Jogador.y - 1, Jogador.x};


}