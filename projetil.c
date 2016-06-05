#include "bibfis.h"
#include "xwc.h"
#include "graficos.h"
#include <stdlib.h>
#include "projetil.h"

projetil novo_projetil (double x, double y, WINDOW* w1, PIC MAPA) {
    projetil p = malloc (sizeof (struct Projetil));
	
	p->mask = NewMask(MAPA, 32, 32);
	p->pic = ReadPic(w1, "imagens/projeteis/projetil.xpm", p->mask);
    //VALORES PRECISAM SER AJUSTADOS
    p->massa = 10;
    p->x = x;
    p->y = y;
    p->velx = 500; //SUBSTITUIR POR FUNCAO DA INCLINACAO
    p->vely = 500; //SUBSTITUIR POR FUNCAO DA INCLINACAO
    p->tempo = 1000;
    p->morto = 0;
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
    if (p->x > WIDTH) p->x -= WIDTH + 50;
    if (p->y > HEIGHT) p->y -= HEIGHT + 50;
    p->tempo -= dt;
    if (p->tempo <= 0) p->morto = 1;
}

void imprime_projetil (projetil p, WINDOW* w1) {
    PIC picture = NewPic (w1, WIDTH, HEIGHT);
	PutPic (picture, p->pic, 0, 0, WIDTH, HEIGHT, reduz_coordenada (p->x), reduz_coordenada (p->y));
	SetMask (w1, p->mask);
	PutPic (w1, picture, reduz_coordenada (p->x), reduz_coordenada (p->y), WIDTH, HEIGHT, reduz_coordenada (p->x), reduz_coordenada (p->y));
    UnSetMask (w1);
    FreePic (picture);
}
