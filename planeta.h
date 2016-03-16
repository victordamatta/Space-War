struct Planeta {
    double massa,
    double r
};

typedef struct Planeta * planeta;

/* Constructor para um planeta */
planeta nova_planeta (double massa, double r);

/* Calcula a atracao gravitacional da planeta n no ponto (x, y) */
double atracao_planeta (planeta n, double x, double y);
