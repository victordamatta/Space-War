#ifndef PROJETIL_H
#define PROJETIL_H
#define MAX_MSKS 25
struct Projetil {
    double massa;
    double x;
    double y;
    double velx;
    double vely;
    double tempo;
    int morto;
	MASK msks[MAX_MSKS];
	PIC pic[MAX_MSKS];
	double inclinacao;
	int inc;
	double pos[MAX_MSKS];
	int qnt_pos;
};

typedef struct Projetil * projetil;

/* Constructor para um projetil */
projetil novo_projetil (double x, double y, int inclinacao, WINDOW* w1, PIC MAPA);

/* Destructor para um projetil */
void destroi_projetil (projetil p);

/* Altera a velocidade do projetil p de acordo com o vetor forca f
 * aplicado com duracao dt */
void empurra_projetil (projetil p, forca f, double dt);

/* Calcula a forca gravitacional do projetil p no objeto de massa m localizado em (x, y) */
forca atracao_projetil (projetil p, double x, double y, double m);

/* Altera as coordenadas do projetil de acordo com a velocidade no tempo dt */
void atualiza_projetil (projetil p, double dt);

/* Imprime projetil p na janela principal */
void imprime_projetil (projetil p, WINDOW* w1);
#endif
