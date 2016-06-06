#ifndef GRAFICOS_H
#define GRAFICOS_H
/* Tamanho da tela */
#define WIDTH 800
#define HEIGHT 800
#define AJUSTE_NAVE 75

/* Recebe um ponto na escala planetaria e devolve o ponto correspondente na 
 * escala grafica */
int reduz_coordenada (double x);
/* Recebe uma distancia na escala grafica e devolve a distancia correspondente na 
 * escala planetaria */
double amplia_distancia (int x);
#endif
