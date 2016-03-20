#include "nave.h"
#include <stdlib.h>

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
    free (n->nome);
    free (n);
}

void empurra_nave (nave n, forca f, double dt);

double atracao_nave (nave n, double x, double y);

void atualiza_nave (nave n, double dt);
