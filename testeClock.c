#include <stdio.h>
#include <time.h>

int main() {
    clock_t comeco, final;
    float tot;

    printf("%d", CLOCKS_PER_SEC);

    //printar algo a cada 1 segundo
    comeco = clock();
    final = clock();
    while (1) {
        tot = (float)(final - comeco) / CLOCKS_PER_SEC;
        while (tot < 5) {
            final = clock();
            tot = (float)(final - comeco) / CLOCKS_PER_SEC;
        }
        printf("se passaram 2 segundos...\n");
        comeco = clock();
        final = clock();
    }
    

    return 0;
}