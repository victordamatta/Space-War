#include "bibfis.h"
#include "planeta.h"
#include <stdlib.h>
#include <stdio.h>

planeta novo_planeta (double massa, double r) {
    planeta p = malloc (sizeof (struct Planeta));
    p->massa = massa;
    p->r = r;
    return p; // Nao tinha return aqui
}

void destroi_planeta (planeta p) {
    free (p);
}

forca atracao_planeta (planeta p, double x, double y, double m) {
    return atracao (x, y, m, 400, 300, p->massa);
}
