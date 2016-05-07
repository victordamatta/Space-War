#include "bibfis.h"
#include "nave.h"
#include "xwc.h"
#include <stdlib.h>
#include <string.h> 
#include <stdio.h>
#include <unistd.h>

PIC *tardis = malloc (16 * sizeof (PIC));

tardis[0] = ReadPic (w1, "tardis0.xpm", NULL);
tardis[1] = ReadPic (w1, "tardis22'30.xpm", NULL);
tardis[2] = ReadPic (w1, "tardis45.xpm", NULL);
tardis[3] = ReadPic (w1, "tardis66'30.xpm", NULL);
tardis[4] = ReadPic (w1, "tardis90.xpm", NULL);
tardis[5] = ReadPic (w1, "tardis112'30.xpm", NULL);
tardis[6] = ReadPic (w1, "tardis135.xpm", NULL);
tardis[7] = ReadPic (w1, "tardis157'30.xpm", NULL);
tardis[8] = ReadPic (w1, "tardis180.xpm", NULL);
tardis[9] = ReadPic (w1, "tardis202'30.xpm", NULL);
tardis[10] = ReadPic (w1, "tardis225.xpm", NULL);
tardis[11] = ReadPic (w1, "tardis247'30.xpm", NULL);
tardis[12] = ReadPic (w1, "tardis270.xpm", NULL);
tardis[13] = ReadPic (w1, "tardis292'30.xpm", NULL);
tardis[14] = ReadPic (w1, "tardis315.xpm", NULL);
tardis[15] = ReadPic (w1, "tardis337'30.xpm", NULL);

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
