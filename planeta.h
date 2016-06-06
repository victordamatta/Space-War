#ifndef PLANETA_H
#define PLANETA_H
#define PLANETA_RAIO 80
struct Planeta {
    double massa;
    double r;
};

typedef struct Planeta * planeta;

/* Constructor para um planeta */
planeta novo_planeta (double massa, double r);

/* Destructor para um planeta */
void destroi_planeta (planeta p);

/* Calcula a atracao gravitacional do planeta n no objeto de massa m localizado em (x, y) */
forca atracao_planeta (planeta p, double x, double y, double m);
#endif
