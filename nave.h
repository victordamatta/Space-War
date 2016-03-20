struct Nave {
    char* nome;
    double massa;
    double x;
    double y;
    double velx;
    double vely;
};

typedef struct Nave * nave;

/* Constructor para uma nave */
nave nova_nave (char* nome, double massa, double x, double y, double velx, double vely);

/* Destructor para uma nave */
void destroi_nave (nave n);

/* Altera a velocidade da nave n de acordo com o vetor forca f
 * aplicado com duracao dt */
void empurra_nave (nave n, forca f, double dt);

/* Calcula a atracao gravitacional da nave n no ponto (x, y) */
double atracao_nave (nave n, double x, double y);

/* Altera as coordenadas da nave de acordo com a velocidade no tempo dt */
void atualiza_nave (nave n, double dt);
