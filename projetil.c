#include "bibfis.h"
#include <stdio.h>
#include "xwc.h"
#include <stdlib.h>
#include <unistd.h>
#include "projetil.h"
#define MAX_MSKS 25
WINDOW *w1;

projetil novo_projetil (double massa, double x, double y, double velx, double vely, double tempo, int inclin) {   
	projetil p = malloc (sizeof (struct Projetil));
	
	PIC MAPA;
 	MASK msks[MAX_MSKS];
	PIC pic[MAX_MSKS];
  
	MAPA = ReadPic(w1, "todo.xpm", NULL);	

	p->msks[0] = NewMask(MAPA, 32, 32);
	p->msks[1] = NewMask(MAPA,32,32);
	/*	
	p->msks[2] = NewMask(MAPA,32, 32);
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
	p->msks[17] = NewMask(MAPA, 32, 32);
	p->msks[18] = NewMask(MAPA, 32, 32);
	p->msks[19] = NewMask(MAPA, 32, 32);
	p->msks[20] = NewMask(MAPA, 32, 32);
	p->msks[21] = NewMask(MAPA, 32, 32);
	p->msks[22] = NewMask(MAPA, 32, 32);
	p->msks[23] = NewMask(MAPA, 32, 32);
	p->msks[24] = NewMask(MAPA, 32, 32);
	*/

	p->pic[0] = ReadPic(w1,"imagens/projeteis/xpm/p-0.xpm", p->msks[0]);
	p->pic[1] = ReadPic(w1,"imagens/projeteis/xpm/p-180.xpm", p->msks[1]);
	/*
	p->pic[2] = ReadPic(w1,"p-30.xpm", p->msks[2]);
	p->pic[3] = ReadPic(w1,"p-45.xpm", p->msks[3]);
	p->pic[4] = ReadPic(w1,"p-60.xpm", p->msks[4]);
	p->pic[5] = ReadPic(w1,"p-75.xpm", p->msks[5]);
	p->pic[6] = ReadPic(w1,"p-90.xpm", p->msks[6]);
	p->pic[7] = ReadPic(w1,"p-105.xpm", p->msks[7]);
	p->pic[8] = ReadPic(w1,"p-120.xpm", p->msks[8]);
	p->pic[9] = ReadPic(w1,"p-135.xpm", p->msks[9]);
	p->pic[10] = ReadPic(w1,"p-150.xpm", p->msks[10]);
	p->pic[11] = ReadPic(w1,"p-165.xpm", p->msks[11]);
	p->pic[12] = ReadPic(w1,"p-180.xpm", p->msks[12]);
	p->pic[13] = ReadPic(w1,"p-195.xpm", p->msks[13]);
	p->pic[14] = ReadPic(w1,"p-210.xpm", p->msks[14]);
	p->pic[15] = ReadPic(w1,"p-225.xpm", p->msks[15]);
	p->pic[16] = ReadPic(w1,"p-240.xpm", p->msks[16]);
	p->pic[17] = ReadPic(w1,"p-255.xpm", p->msks[17]);
	p->pic[18] = ReadPic(w1,"p-270.xpm", p->msks[18]);
	p->pic[19] = ReadPic(w1,"p-285.xpm", p->msks[19]);
	p->pic[20] = ReadPic(w1,"p-300.xpm", p->msks[20]);
	p->pic[21] = ReadPic(w1,"p-315.xpm", p->msks[21]);
	p->pic[22] = ReadPic(w1,"p-330.xpm", p->msks[22]);
	p->pic[23] = ReadPic(w1,"p-345.xpm", p->msks[23]);
	p->pic[24] = ReadPic(w1,"p-360.xpm", p->msks[24]);
	*/   

	p->massa = massa;
    p->x = x;
    p->y = y;
    p->velx = velx;
    p->vely = vely;
    p->tempo = tempo;
   	p->morto = 0;
	p->inclin = inclin/15;
	p->qnt_pos = 0;
	
    return p;
}

void imprime_projetil (projetil p, WINDOW *w1, PIC picture) {	
	PutPic(picture,p->pic[p->inclin],0,0,800, 600,p->x,p->y);
	SetMask(w1,p->msks[p->inclin]);
	PutPic(w1,picture,p->x,p->y,800, 600,p->x,p->y);
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


