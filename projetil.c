#include "bibfis.h"
#include "xwc.h"
#include "graficos.h"
#include <stdlib.h>
#include "projetil.h"

projetil novo_projetil (double massa, double x, double y, double velx, double vely, double tempo, int inclinacao, WINDOW* w1) {
    projetil p = malloc (sizeof (struct Projetil));
	PIC MAPA = ReadPic(w1, "imagens/cenario.xpm", NULL);

    int i;
    for (i = 0; i <= 16; i++)
        p->msks[i] = NewMask(MAPA, 32, 32);

    char file_name[] = "imagens/projeteis/projetil-00.xpm";
    for (i = 0; i <= 16; i++) {
        file_name[27] = i/10 + 48;
        file_name[28] = i%10 + 48;
		p->pic[i] = ReadPic (w1, file_name, p->msks[i]);
    }

    p->massa = massa;
    p->x = x;
    p->y = y;
    p->velx = velx;
    p->vely = vely;
    p->tempo = tempo;
    p->morto = 0;
    p->inc = inclinacao;
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
    if (p->x > WIDTH) p->x -= WIDTH + 50;
    if (p->y > HEIGHT) p->y -= HEIGHT + 50;
    p->tempo -= dt;
    if (p->tempo <= 0) p->morto = 1;
}

void imprime_projetil (projetil p, WINDOW* w1) {
    PIC picture = NewPic (w1, WIDTH, HEIGHT);
	PutPic (picture, p->pic[p->inc], 0, 0, WIDTH, HEIGHT, reduz_coordenada (p->x), reduz_coordenada (p->y));
	SetMask (w1, p->msks[p->inc]);
	PutPic (w1, picture, reduz_coordenada (p->x), reduz_coordenada (p->y), WIDTH, HEIGHT, reduz_coordenada (p->x), reduz_coordenada (p->y));
    UnSetMask (w1);
    FreePic (picture);
}
