#include "bibfis.h"
#include "xwc.h"
#include <stdlib.h>
#include <string.h> 
#include <stdio.h>
#include "nave.h"

nave nova_nave (char* nome, double massa, double x, double y, double velx, double vely) {
    nave n = malloc (sizeof (struct Nave));
	n->nome = nome;
    n->massa = massa;
    n->x = x;
    n->y = y;
    n->velx = velx;
    n->vely = vely;
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
}

void imprime_nave (nave n, WINDOW* w1, PIC picture) {
    PutPic (picture, n->pic[0], 0, 0, 800, 600, n->x, n->y);
    SetMask (w1, n->msks[0]);
    PutPic (w1, picture, n->x, n->y, 800, 600, n->x, n->y);
}
