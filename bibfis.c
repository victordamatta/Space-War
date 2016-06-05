#include "bibfis.h"
#include <stdio.h>
#include <math.h>

void compara (double tx, double rx, double ty, double ry) {

    const double ERR = 0.000001;
    if (tx < rx + ERR && tx > rx - ERR) {
        if (ty < ry + ERR && ty > ry - ERR) {
            printf ("CORRETO\n");
            return;
        }
    }
    printf ("INCORRETO\n");
}

forca atracao (double xa, double ya, double ma, double xb, double yb, double mb){

    forca res;
    double g = (6.67408);
    double dist, ft;
    double dx = xb - xa;
    double dy = yb - ya;

    dist = dx*dx + dy*dy;
    dist = sqrt(dist);

    ft = (g * ma * mb) / (dist*dist);
    ft = ft / pow(10, 11);
	
    res.x = ft * (dx / dist);
    res.y = ft * (dy / dist);


    return res;
}

forca resultante (forca a, forca b){

    forca re;

    re.x = a.x + b.x;
    re.y = a.y + b.y;

    return re;
}

void velocidade (forca aplicada, double massa, double t, double *vx, double *vy){

    *vx += (aplicada.x * t) / massa;
    *vy += (aplicada.y * t) / massa;
}

componentes decomposicao (double intensidade, int inclinacao) {

    double xmod[] = {0, 0.382, 0.707, 0.923, 1, 0.923, 0.707, 0.382, 0, -0.382, -0.707, -0.923, -1, -0.923, -0.707, -0.382};
    double ymod[] = {1, 0.923, 0.707, 0.382, 0, -0.382, -0.707, -0.923, -1, -0.923, -0.707, -0.382, 0, 0.382, 0.707, 0.923};
    struct Componentes comp;
    comp.x = xmod[inclinacao]*intensidade;
    comp.y = ymod[inclinacao]*intensidade;
    return comp;
}
/*
int main (){

    forca ap, teste, fa, fb;
    double vx, vy;

    ap.x = 2;
    ap.y = 3;
    vx = 1;
    vy = 3;

    // A esta em (1,2) e tem M = 7000000, e B esta em (5,5) e tem M = 8000000
    fa = atracao(1, 2, 7000000, 5, 5, 8000000);
    fb = atracao(5, 5, 8000000, 1, 2, 7000000);

    teste = resultante (fa, fb);
    printf ("TESTE resultante: ");
    compara (teste.x, 0.0, teste.y, 0.0);

    teste = resultante (fa, ap);
    printf ("TESTE resultante: ");
    compara (teste.x, 121.599514, teste.y, 92.699635);

    printf ("TESTE atracao: ");
    compara (fa.x, 119.599514, fa.y, 89.699635);
    printf ("TESTE atracao: ");
    compara (fb.x, -119.599514, fb.y, -89.699635);

    velocidade (ap, 3, 10, &vx, &vy);
    printf ("TESTE velocidade: ");
    compara (vx, 7.666667, vy, 13.0);

    return 0;
}
*/
