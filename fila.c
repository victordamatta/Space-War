#include "projetil.h"
#include "fila.h"
#include <stdlib.h>

fila constroi_fila (int max) {
    fila f = malloc (sizeof (struct Fila));
    f->vet = malloc (max * sizeof (projetil));
    f->ini = 0;
    f->fim = 0;
    f->max = max;
    f->tam = 0;
    return f;
}

void destroi_fila (fila f) {
    free (f->vet);
    free (f);
}

void enqueue (fila f, projetil p) {
    f->vet[f->fim] = p;
    f->fim = (f->fim + 1) % f->max;
    f->tam++;
}

projetil dequeue (fila f) {
    projetil aux = f->vet[f->ini];
    f->ini = (f->ini + 1) % f->max;
    return aux;
}
