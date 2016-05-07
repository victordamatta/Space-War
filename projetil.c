#include "bibfis.h"
#include "xwc.h"
#include <stdlib.h>
#include "projetil.h"
extern WINDOW* w1;

projetil novo_projetil (double massa, double x, double y, double velx, double vely, double tempo, int inc) {
    projetil p = malloc (sizeof (struct Projetil));
	PIC MAPA = ReadPic(w1, "imagens/oficial-plan.xpm", NULL);
	p->msks[0] = NewMask(MAPA, 32, 32);
	p->msks[1] = NewMask(MAPA, 32, 32);
	p->pic[0] = ReadPic(w1, "imagens/projeteis/xpm/p-0.xpm", p->msks[0]);
	p->pic[1] = ReadPic(w1, "imagens/projeteis/xpm/p-180.xpm", p->msks[1]);

    p->massa = massa;
    p->x = x;
    p->y = y;
    p->velx = velx;
    p->vely = vely;
    p->tempo = tempo;
    p->morto = 0;
    p->inc = inc / 15;
    p->qnt_pos = 0;
    return p;
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

void imprime_projetil (projetil p, PIC picture) {
	PutPic (picture, p->pic[p->inc], 0, 0, 800, 600, p->x, p->y);
	SetMask (w1, p->msks[p->inc]);
	PutPic (w1, picture, p->x, p->y, 800, 600, p->x, p->y);
}
