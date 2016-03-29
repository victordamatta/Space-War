#include "bibfis.h"
#include "projetil.h"
#include <stdlib.h>

projetil novo_projetil (double massa, double x, double y, double velx, double vely) {
    projetil p = malloc (sizeof (struct Projetil));
    p->massa = massa;
    p->x = x;
    p->y = y;
    p->velx = velx;
    p->vely = vely;
}

void destroi_projetil (projetil p) {
    free (p);
}

void empurra_projetil (projetil p, forca f, double dt) {
    velocidade (f, p->massa, dt, &(p->velx), &(p->vely));
}

void atualiza_projetil (projetil p, double dt) {
    p->x += dt * p->velx;
    p->y += dt * p->vely;
}
