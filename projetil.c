#include "bibfis.h"
#include "xwc.h"
#include <stdlib.h>
#include "projetil.h"

projetil novo_projetil (double massa, double x, double y, double velx, double vely, double tempo, double inclinacao, WINDOW* w1) {
    projetil p = malloc (sizeof (struct Projetil));
	PIC MAPA = ReadPic(w1, "imagens/cenario.xpm", NULL);
	p->msks[0] = NewMask(MAPA, 32, 32);
	p->msks[1] = NewMask(MAPA, 32, 32);
	p->msks[2] = NewMask(MAPA, 32, 32);
	p->msks[3] = NewMask(MAPA, 32, 32);
	p->msks[4] = NewMask(MAPA, 32, 32);
	p->msks[5] = NewMask(MAPA, 32, 32);
	p->msks[6] = NewMask(MAPA, 32, 32);
	p->msks[7] = NewMask(MAPA, 32, 32);
	p->msks[8] = NewMask(MAPA, 32, 32);
	p->msks[9] = NewMask(MAPA, 32, 32);
	p->msks[10] = NewMask(MAPA, 32, 32);
	p->msks[11] = NewMask(MAPA, 32, 32);
	p->msks[12] = NewMask(MAPA, 32, 32);
	p->msks[13] = NewMask(MAPA, 32, 32);
	p->msks[14] = NewMask(MAPA, 32, 32);
	p->msks[15] = NewMask(MAPA, 32, 32);
	p->msks[16] = NewMask(MAPA, 32, 32);
	
	p->pic[0] = ReadPic(w1, "imagens/projeteis/projetil-0.xpm", p->msks[0]);
	p->pic[1] = ReadPic(w1, "imagens/projeteis/projetil-22.30.xpm", p->msks[1]);
	p->pic[2] = ReadPic(w1, "imagens/projeteis/projetil-44.60.xpm", p->msks[2]);
	p->pic[3] = ReadPic(w1, "imagens/projeteis/projetil-66.90.xpm", p->msks[3]);
	p->pic[4] = ReadPic(w1, "imagens/projeteis/projetil-89.20.xpm", p->msks[4]);
	p->pic[5] = ReadPic(w1, "imagens/projeteis/projetil-222.50.xpm", p->msks[5]);
	p->pic[6] = ReadPic(w1, "imagens/projeteis/projetil-133.80.xpm", p->msks[6]);
	p->pic[7] = ReadPic(w1, "imagens/projeteis/projetil-156.10.xpm", p->msks[7]);
	p->pic[8] = ReadPic(w1, "imagens/projeteis/projetil-178.40.xpm", p->msks[8]);
	p->pic[9] = ReadPic(w1, "imagens/projeteis/projetil-200.70.xpm", p->msks[9]);
	p->pic[10] = ReadPic(w1, "imagens/projeteis/projetil-223.00.xpm", p->msks[10]);
	p->pic[11] = ReadPic(w1, "imagens/projeteis/projetil-245.30.xpm", p->msks[11]);
	p->pic[12] = ReadPic(w1, "imagens/projeteis/projetil-267.60.xpm", p->msks[12]);
	p->pic[13] = ReadPic(w1, "imagens/projeteis/projetil-289.90.xpm", p->msks[13]);
	p->pic[14] = ReadPic(w1, "imagens/projeteis/projetil-312.20.xpm", p->msks[14]);
	p->pic[15] = ReadPic(w1, "imagens/projeteis/projetil-334.50.xpm", p->msks[15]);
	p->pic[16] = ReadPic(w1, "imagens/projeteis/projetil-356.80.xpm", p->msks[16]);

    p->massa = massa;
    p->x = x;
    p->y = y;
    p->velx = velx;
    p->vely = vely;
    p->tempo = tempo;
    p->morto = 0;
    p->inc = inclinacao / 22.30;
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
    if (p->x > 800) p->x -= 850;
    if (p->y > 600) p->y -= 650;
    p->tempo -= dt;
    if (p->tempo <= 0) p->morto = 1;
}

void imprime_projetil (projetil p, WINDOW* w1, PIC picture) {
	PutPic (picture, p->pic[p->inc], 0, 0, 800, 600, p->x, p->y);
	SetMask (w1, p->msks[p->inc]);
	PutPic (w1, picture, p->x, p->y, 800, 600, p->x, p->y);
}
