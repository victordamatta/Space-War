#include "bibfis.h"
#include "xwc.h"
#include "graficos.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "projetil.h"
#include "nave.h"

nave nova_nave (char* nome, double massa, double x, double y, double velx, double vely, WINDOW* w1, int player, int inclinacao) {
    nave n = malloc (sizeof (struct Nave));
    PIC MAPA = ReadPic(w1, "imagens/cenario.xpm", NULL);

    int i;
    for (i = 0; i < 16; i++)
        n->msks[i] = NewMask (MAPA, 32, 32);

    char file_name[] = "imagens/naves/nave1-00.xpm";
    file_name[18] = player + 48;
    for (i = 0; i < 16; i++) {
        file_name[20] = i/10 + 48;
        file_name[21] = i%10 + 48;
		n->pic[i] = ReadPic (w1, file_name, n->msks[i]);
    }

	n->nome = nome;
    n->massa = massa;
    n->x = x;
    n->y = y;
    n->velx = velx;
    n->vely = vely;
    n->inc = inclinacao;
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
    if (reduz_coordenada (n->x) > WIDTH) n->x -= amplia_distancia (WIDTH + 50);
    else if (reduz_coordenada (n->x) < 0) n->x += amplia_distancia (WIDTH + 50);
    if (reduz_coordenada (n->y) > HEIGHT) n->y -= amplia_distancia (HEIGHT + 50);
    else if (reduz_coordenada (n->y) < 0) n->y += amplia_distancia (HEIGHT + 50);
}

void imprime_nave (nave n, WINDOW* w1) {
    PIC picture = NewPic (w1, WIDTH, HEIGHT);
    PutPic (picture, n->pic[n->inc], 0, 0, WIDTH, HEIGHT, reduz_coordenada (n->x) - AJUSTE_NAVE, reduz_coordenada (n->y) - AJUSTE_NAVE);
    SetMask (w1, n->msks[n->inc]);
    PutPic (w1, picture, reduz_coordenada (n->x) - AJUSTE_NAVE, reduz_coordenada (n->y) - AJUSTE_NAVE, WIDTH, HEIGHT, reduz_coordenada (n->x) - AJUSTE_NAVE, reduz_coordenada (n->y) - AJUSTE_NAVE);
    UnSetMask (w1);
    FreePic (picture);
}

void rotaciona_nave (nave n, int dir) {
    n->inc = (n->inc + dir) % 16;
    if (n->inc < 0) n->inc += 16;
}

projetil atira (nave n, PIC mask, PIC pic) {
    componentes comp = decomposicao (amplia_distancia (45), n->inc);
    return novo_projetil (n->x + comp.x, n->y + comp.y, n->inc, mask, pic);
}

int colisao (nave n, double x, double y, int size) {
    double dist = amplia_distancia (size + NAVE_RAIO);
    if ((n->x - x)*(n->x - x) + (n->y - y)*(n->y - y) < dist*dist) return 1;
    return 0;
}
