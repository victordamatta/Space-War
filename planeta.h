struct Planeta {
    double massa,
    double r
};

typedef struct Planeta * planeta;

/* Constructor para um planeta */
planeta novo_planeta (double massa, double r);

/* Calcula a atracao gravitacional do planeta n no ponto (x, y) */
double atracao_planeta (planeta p, double x, double y);
