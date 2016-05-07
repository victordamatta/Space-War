#ifndef NAVE_H
#define NAVE_H
struct Nave {
    char* nome;
    double massa;
    double x;
    double y;
    double velx;
    double vely;
    PIC ImagemNave;
};

typedef struct Nave * nave;

/* Constructor para uma nave */
nave nova_nave (char* nome, double massa, double x, double y, double velx, double vely);

/* Destructor para uma nave */
void destroi_nave (nave n);

/* Altera a velocidade da nave n de acordo com o vetor forca f
 * aplicado com duracao dt */
void empurra_nave (nave n, forca f, double dt);

/* Calcula a forca gravitacional da nave n no objeto de massa m localizado em (x, y) */
forca atracao_nave (nave n, double x, double y, double m);

/* Altera as coordenadas da nave de acordo com a velocidade no tempo dt */
void atualiza_nave (nave n, double dt);
#endif
