#include <unistd.h>
#include <stdlib.h>
#include <ncurses\ncurses.h>
#include <time.h>
#include <string.h>

// compilar com gcc space2.c -o space.exe -lncursesw para linkagem dinâmica
// compular com gcc space2.c -o space.exe -lncurses -DNCURSES_STATIC para linkagem estática

#define HEIGHT 20
#define WIDTH 41
#define MAXMOVCOOLDOWN 3

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
    int visivel;
}enemy;

// variaveis globais
player jogador;
shot tiros[100];
shot tirosEnemy[100];
enemy inimigos[5];
int inimigomovcooldown = MAXMOVCOOLDOWN;


player newPlayer(WINDOW *win, int y, int x, int lifes, char format);

shot newShot(WINDOW *win, int y, int x, int lancado, char format);

enemy newEnemy(WINDOW *win, int y, int x, int velocidade, int direcao, char *format, int visivel);

void mover( void );

void atualizar( void );

void moverTiro( void );

void moverInimigo( void );

int main() {
    int gameOver = 0;

    initscr();
    cbreak();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);

    WINDOW *tela = newwin(HEIGHT, WIDTH, 5, 30); 
    box(tela, 0, 0);
    refresh(); // atualizar tudo dentro da janela principal

    jogador = newPlayer(tela, HEIGHT - 2, WIDTH / 2, 1, '@');

    for (int i = 0; i < 100; i++) {
        tiros[i] = newShot(tela, 0, 0, 0, '^');
        tirosEnemy[i] = newShot(tela, 0, 0, 0 , '*');
    }

    for (int i = 0; i < 5; i++) {
        inimigos[i] = newEnemy(tela, 10, 8 + 6*i, 1, -1, "=O=", 1);

    }

    srand(time(NULL));

    while (!gameOver) {
        mover(); //jogador
        moverTiro();
        moverInimigo();   
        atualizar(); // atualiza todos os elementos
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

enemy newEnemy(WINDOW *win, int y, int x, int velocidade, int direcao, char * format, int visivel) {
    enemy temp = {win, y, x, velocidade, direcao, format, visivel};
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

        if (tirosEnemy[i].lancado == 1) {

            mvwaddch(tirosEnemy[i].win, tirosEnemy[i].y, tirosEnemy[i].x, ' ');
            wrefresh(tirosEnemy[i].win);

            if (tirosEnemy[i].y < HEIGHT - 2) {
                tirosEnemy[i].y++;
            } else {
                tirosEnemy[i].lancado = 0;
            }
        }
    }
    
}

void moverInimigo( void ) {
    // iteração para cada inimigo
    int atirar;
    inimigomovcooldown--;

    //dentro da iteração de cada inimigo, verificar se há algum tiro na msm posição que ele
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 100; j++) {
            // se o inimigo está visivel e o tiro está em uso
         if (inimigos[i].visivel == 1 && tiros[j].lancado == 1) {
            if ((tiros[j].x == inimigos[i].x || tiros[j].x == inimigos[i].x + 1 || tiros[j].x == inimigos[i].x + 2) 
                && (tiros[j].y == inimigos[i].y)) {
                // se todos os critérios forem atendidos, o inimigo sofreu um tiro
                inimigos[i].format = "   ";
                tiros[j].lancado = 0;
                inimigos[i].visivel = 0;
                }
            }
        }
    }

    if (inimigomovcooldown <= 0){
        inimigomovcooldown = MAXMOVCOOLDOWN;

        for (int i = 0; i < 5; i++) {

            mvwprintw(inimigos[i].win, inimigos[i].y, inimigos[i].x, "%s", "   ");
            wrefresh(inimigos[i].win);

            for (int k = 0; k < 5; k++) {
                mvprintw(0, 4*k, "%d", inimigos[k].x);
                refresh();
                mvprintw(0, 4*k, "%d", inimigos[k].x);
                refresh();
            }
        
            if (inimigos[i].x < WIDTH - 4 && inimigos[i].x > 1) {
                inimigos[i].x += inimigos[i].direcao;
            } else {
                for (int j = 0; j < 5; j++) {
                    mvwprintw(inimigos[j].win, inimigos[j].y, inimigos[j].x, "%s", "   ");
                    wrefresh(inimigos[j].win);

                    inimigos[j].direcao *= -1;
                    
                    if (inimigos[i].x >= WIDTH - 4) {
                        inimigos[j].x--;
                    } else if (inimigos[i].x <= 1) {
                        inimigos[j].x++;
                    }

                    inimigos[j].y++;
                }  
            }
            

        //apenas os inimigos vivos/visiveis atiram
            if (inimigos[i].visivel == 1) {
                atirar = rand() % 100;
                //criterio para atirar!
                if (atirar%15 == 0) {
                    for (int j = 0; j < 100; j++) {
                        if (tirosEnemy[j].lancado == 0) {
                            tirosEnemy[j].y = inimigos[i].y;
                            tirosEnemy[j].x = inimigos[i].x + 1;
                            tirosEnemy[j].lancado = 1;
                            break;
                        }
                    }

                }
            }

        }   

    }
}

void atualizar (void) {
    mvwaddch(jogador.win, jogador.y, jogador.x, jogador.format);
    wrefresh(jogador.win);

    for (int i = 0; i < 5; i++) {
        mvwprintw(inimigos[i].win, inimigos[i].y, inimigos[i].x, "%s", inimigos[i].format);
        wrefresh(inimigos[i].win);
    }

    for (int i = 0; i < 100; i++) {
        if (tiros[i].lancado == 1) {
            mvwaddch(tiros[i].win, tiros[i].y, tiros[i].x, tiros[i].format);
            wrefresh(tiros[i].win);
        }

        if (tirosEnemy[i].lancado == 1) {
            mvwaddch(tirosEnemy[i].win, tirosEnemy[i].y, tirosEnemy[i].x, tirosEnemy[i].format);
            wrefresh(tirosEnemy[i].win);
        }
    }

 
}

