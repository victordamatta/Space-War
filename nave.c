#include "bibfis.h"
#include "xwc.h"
#include <stdlib.h>
#include <string.h> 
#include <stdio.h>
#include "nave.h"

nave nova_nave (char* nome, double massa, double x, double y, double velx, double vely, WINDOW* w1, int player, double inclinacao) {
    nave n = malloc (sizeof (struct Nave));
    PIC MAPA = ReadPic(w1, "imagens/cenario.xpm", NULL);

    int i;
    for (i = 0; i <= 16; i++) 
        n->msks[i] = NewMask (MAPA, 32, 32);

    char file_name[] = "imagens/naves/nave1-00.xpm";
    file_name[18] = player + 48;
    for (i = 0; i <= 16; i++) {
        file_name[20] = i/10 + 48;
        file_name[21] = i%10 + 48;
		n->pic[i] = ReadPic (w1, file_name, n->msks[i]);
    }

	n->nome = nome;
    n->massa = massa;
    n->x = x;
    n->y = y;
    n->velx = velx;
    n->vely = vely;
    n->inc = inclinacao / 22.30;
    return n;
}

void destroi_nave (nave n) {
    free (n);
}

void empurra_nave (nave n, forca f, double dt) {
    velocidade (f, n->massa, dt, &(n->velx), &(n->vely));
}

forca atracao_nave (nave n, double x, double y, double m) {
    return atracao (x, y, m, n->x, n->y, n->massa);
}

void atualiza_nave (nave n, double dt) {
    n->x += dt * n->velx;
    n->y += dt * n->vely;
    if (n->x > 800) n->x -= 850;
    if (n->y > 600) n->y -= 650;
}

void imprime_nave (nave n, WINDOW* w1, PIC picture) {
    PutPic (picture, n->pic[n->inc], 0, 0, 800, 600, n->x, n->y);
    SetMask (w1, n->msks[n->inc]);
    PutPic (w1, picture, n->x, n->y, 800, 600, n->x, n->y);
}
