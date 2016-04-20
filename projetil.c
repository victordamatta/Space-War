#include "bibfis.h"
#include "projetil.h"
#include <stdlib.h>

projetil novo_projetil (double massa, double x, double y, double velx, double vely, double tempo) {
    projetil p = malloc (sizeof (struct Projetil));
    p->massa = massa;
    p->x = x;
    p->y = y;
    p->velx = velx;
    p->vely = vely;
    p->tempo = tempo;
    p->morto = 0;
    return p; // Nao tinha return aqui
}

void destroi_projetil (projetil p) {
    free (p);
}

void empurra_projetil (projetil p, forca f, double dt) {
    velocidade (f, p->massa, dt, &(p->velx), &(p->vely));
}

forca atracao_projetil (projetil p, double x, double y, double m) {
    return atracao (x, y, m, p->x, p->y, p->massa);
}

void atualiza_projetil (projetil p, double dt) {
    p->x += dt * p->velx;
    p->y += dt * p->vely;
    p->tempo -= dt;
    if (p->tempo <= 0) p->morto = 1;
}
