#include "bibfis.h"
#include "xwc.h"
#include <stdlib.h>
#include <string.h> 
#include <stdio.h>
#include "nave.h"

nave nova_nave (char* nome, double massa, double x, double y, double velx, double vely, WINDOW* w1, int player, double inclinacao) {
    nave n = malloc (sizeof (struct Nave));
    PIC MAPA = ReadPic(w1, "imagens/cenario.xpm", NULL);
    
    n->msks[0] = NewMask (MAPA, 32, 32);
	n->msks[1] = NewMask (MAPA, 32, 32);
	n->msks[2] = NewMask (MAPA, 32, 32);
	n->msks[3] = NewMask (MAPA, 32, 32);
	n->msks[4] = NewMask (MAPA, 32, 32);
	n->msks[5] = NewMask (MAPA, 32, 32);
	n->msks[6] = NewMask (MAPA, 32, 32);
	n->msks[7] = NewMask (MAPA, 32, 32);
	n->msks[8] = NewMask (MAPA, 32, 32);
	n->msks[9] = NewMask (MAPA, 32, 32);
	n->msks[10] = NewMask (MAPA, 32, 32);
	n->msks[11] = NewMask (MAPA, 32, 32);
	n->msks[12] = NewMask (MAPA, 32, 32);
	n->msks[13] = NewMask (MAPA, 32, 32);
	n->msks[14] = NewMask (MAPA, 32, 32);
	n->msks[15] = NewMask (MAPA, 32, 32);
	n->msks[16] = NewMask (MAPA, 32, 32);
		
    if(player == 1 ) {

		n->pic[0] = ReadPic (w1, "imagens/naves/nave1-0.xpm", n->msks[0]);
		n->pic[1] = ReadPic (w1, "imagens/naves/nave1-22.30.xpm", n->msks[1]);
		n->pic[2] = ReadPic (w1, "imagens/naves/nave1-44.60.xpm", n->msks[2]);
		n->pic[3] = ReadPic (w1, "imagens/naves/nave1-66.90.xpm", n->msks[3]);
		n->pic[4] = ReadPic (w1, "imagens/naves/nave1-89.20.xpm", n->msks[4]);
		n->pic[5] = ReadPic (w1, "imagens/naves/nave1-111.50.xpm", n->msks[5]);
		n->pic[6] = ReadPic (w1, "imagens/naves/nave1-133.80.xpm", n->msks[6]);
		n->pic[7] = ReadPic (w1, "imagens/naves/nave1-156.10.xpm", n->msks[7]);
		n->pic[8] = ReadPic (w1, "imagens/naves/nave1-178.40.xpm", n->msks[8]);
		n->pic[9] = ReadPic (w1, "imagens/naves/nave1-200.70.xpm", n->msks[9]);
		n->pic[10] = ReadPic (w1, "imagens/naves/nave1-223.00.xpm", n->msks[10]);
		n->pic[11] = ReadPic (w1, "imagens/naves/nave1-245.30.xpm", n->msks[11]);
		n->pic[12] = ReadPic (w1, "imagens/naves/nave1-267.60.xpm", n->msks[12]);
		n->pic[13] = ReadPic (w1, "imagens/naves/nave1-289.90.xpm", n->msks[13]);
		n->pic[14] = ReadPic (w1, "imagens/naves/nave1-312.20.xpm", n->msks[14]);
		n->pic[15] = ReadPic (w1, "imagens/naves/nave1-334.50.xpm", n->msks[15]);
		n->pic[16] = ReadPic (w1, "imagens/naves/nave1-356.80.xpm", n->msks[16]);
	}
	
	else if(player == 2) {

		n->pic[0] = ReadPic (w1, "imagens/naves/nave2-0.xpm", n->msks[0]);
		n->pic[1] = ReadPic (w1, "imagens/naves/nave2-22.30.xpm", n->msks[1]);
		n->pic[2] = ReadPic (w1, "imagens/naves/nave2-44.60.xpm", n->msks[2]);
		n->pic[3] = ReadPic (w1, "imagens/naves/nave2-66.90.xpm", n->msks[3]);
		n->pic[4] = ReadPic (w1, "imagens/naves/nave2-89.20.xpm", n->msks[4]);
		n->pic[5] = ReadPic (w1, "imagens/naves/nave2-111.50.xpm", n->msks[5]);
		n->pic[6] = ReadPic (w1, "imagens/naves/nave2-133.80.xpm", n->msks[6]);
		n->pic[7] = ReadPic (w1, "imagens/naves/nave2-156.10.xpm", n->msks[7]);
		n->pic[8] = ReadPic (w1, "imagens/naves/nave2-178.40.xpm", n->msks[8]);
		n->pic[9] = ReadPic (w1, "imagens/naves/nave2-200.70.xpm", n->msks[9]);
		n->pic[10] = ReadPic (w1, "imagens/naves/nave2-223.00.xpm", n->msks[10]);
		n->pic[11] = ReadPic (w1, "imagens/naves/nave2-245.30.xpm", n->msks[11]);
		n->pic[12] = ReadPic (w1, "imagens/naves/nave2-267.60.xpm", n->msks[12]);
		n->pic[13] = ReadPic (w1, "imagens/naves/nave2-289.90.xpm", n->msks[13]);
		n->pic[14] = ReadPic (w1, "imagens/naves/nave2-312.20.xpm", n->msks[14]);
		n->pic[15] = ReadPic (w1, "imagens/naves/nave2-334.50.xpm", n->msks[15]);
		n->pic[16] = ReadPic (w1, "imagens/naves/nave2-356.80.xpm", n->msks[16]);
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
