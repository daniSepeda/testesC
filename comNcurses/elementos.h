#ifndef ELEMENTOS
#define ELEMENTOS

#include "c:\msys64\ucrt64\include\ncursesw\ncurses.h"

typedef struct player {
    WINDOW * winAtual;
    int yAtual;
    int xAtual;
    int yMax;
    int xMax;
    int lifes;
    char format;
}player;

typedef struct shot {
    WINDOW * winAtual;
    int yAtual;
    int xAtual;
    int lancado;
    char format;
}shot;

//atribui valores a uma variável do tipo player
player newPlayer(WINDOW *win, int yAtual, int xAtual, int yMax, int xMax, int lifes, char format);

//move jogador para direita
void moverDireita(player * Jogador);

//move jogador para esquerda
void moverEsquerda(player * Jogador);

// move o jogador de um lado para outro
void mover(player * Jogador, shot *tiro);

// ATENÇÃO !!! Podemos alterar o valor dessa função de void para int para indicar final do jogo
// podemos colocar valores diferentes para derrota e para vitória (ex: -1 para derrota e 1 para vitória)
void atualizar(player *Jogador, shot* tiro);

// iniciar animação de tiro após receber o sinal
void atirar(shot * tiro);

#endif // ELEMENTOS