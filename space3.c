#include <unistd.h>
#include <stdlib.h>
#include <ncurses\ncurses.h>
#include <time.h>
#include <string.h>

// compilar com gcc space2.c -o space.exe -lncursesw

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

typedef struct enemy {
    WINDOW *win;
    int y;
    int x;
    int velocidade;
    int direcao;
    char *format;
}enemy;

player jogador;
shot tiros[100];
enemy inimigos[5];
clock_t contInicial, contFinal;

player newPlayer(WINDOW *win, int y, int x, int lifes, char format);

shot newShot(WINDOW *win, int y, int x, int lancado, char format);

enemy newEnemy(WINDOW *win, int y, int x, int velocidade, int direcao, char *format);

void mover( void );

void atualizar( void );

void moverTiro( void );

void moverInimigo( void );

void colisoes( void );

int main() {
    int gameOver = 0;
    float tot;

    initscr();
    cbreak();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);

    WINDOW * tela = newwin(HEIGHT, WIDTH, 5, 30); 
    box(tela, 0, 0);
    refresh(); // atualizar tudo dentro da janela principal

    jogador = newPlayer(tela, HEIGHT - 2, WIDTH / 2, 1, '@');

    for (int i = 0; i < 100; i++) {
        tiros[i] = newShot(tela, 0, 0, 0, '^');
    }

    for (int i = 0; i < 5; i++) {
        inimigos[i] = newEnemy(tela, 10, 8 + 6*i, 1, -1, "=O=");

    }

    contInicial = clock();
    while (!gameOver) {
        contFinal = clock();
        tot = (float)(contFinal - contInicial) / CLOCKS_PER_SEC;

        mover(); //jogador
        moverTiro();
        colisoes();
        if (tot > 0.5) {
            moverInimigo();
            contInicial = clock();
        }
        
        atualizar(); // atualiza todos
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

enemy newEnemy(WINDOW *win, int y, int x, int velocidade, int direcao, char * format) {
    enemy temp = {win, y, x, velocidade, direcao, format};
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
                    tiros[i].y = jogador.y;
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
    for (int i = 0; i < 100; i++) {
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

void moverInimigo( void ) {
    // itereação para cada inimigo
    for (int i = 0; i < 5; i++) {

        mvwprintw(inimigos[i].win, inimigos[i].y, inimigos[i].x, "%s", "   ");
        wrefresh(inimigos[i].win);


        if (inimigos[i].x < WIDTH - 4 && inimigos[i].x > 3) {
            inimigos[i].x += inimigos[i].direcao;
        } else {
            inimigos[i].direcao *= -1;
            inimigos[i].y++;
            inimigos[i].x += inimigos[i].velocidade * inimigos[i].direcao;
        }     
    }   
}
void colisoes( void ) {
    int c1, c2, c3;
    for (int i = 0; i < 5; i++) {
        c1 = (int) mvwinch(inimigos[i].win, inimigos[i].y, inimigos[i].x) & A_CHARTEXT;
        c2 = (int) mvwinch(inimigos[i].win, inimigos[i].y, inimigos[i].x + 1) & A_CHARTEXT;
        c3 = (int) mvwinch(inimigos[i].win, inimigos[i].y, inimigos[i].x + 2) & A_CHARTEXT;

        if (c1 == 94 || c2 == 94 || c3 == 94) {
            inimigos[i].format = "   ";

        }
    } 
}




void atualizar (void) {
    mvwaddch(jogador.win, jogador.y, jogador.x, jogador.format);
    wrefresh(jogador.win);

    for (int i = 0; i < 100; i++) {
        if (tiros[i].lancado == 1) {
            mvwaddch(tiros[i].win, tiros[i].y, tiros[i].x, tiros[i].format);
            wrefresh(tiros[i].win);
        }
    }

    for (int i = 0; i < 5; i++) {
        mvwprintw(inimigos[i].win, inimigos[i].y, inimigos[i].x, "%s", inimigos[i].format);
        wrefresh(inimigos[i].win);
    }
 
}
