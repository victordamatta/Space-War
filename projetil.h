struct Projetil {
    double massa,
    double x,
    double y,
    double velx,
    double vely
};

typedef struct Projetil * projetil;

/* Constructor para um projetil */
projetil novo_projetil (double massa, double x, double y, double velx, double vely);

/* Destructor para um projetil */
void destroi_projetil (projetil p);

/* Altera a velocidade do projetil p de acordo com o vetor forca f
 * aplicado com duracao dt */
void empurra_projetil (projetil p, forca f, double dt);

/* Altera as coordenadas do projetil de acordo com a velocidade no tempo dt */
void atualiza_projetil (projetil p, double dt);
