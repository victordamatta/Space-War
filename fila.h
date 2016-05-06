struct Fila {
    projetil* vet;
    int ini, fim;
    int max, tam;
};

typedef struct Fila* fila;

/* Constructor para fila */
fila constroi_fila (int);

/* Destructor para fila */
void destroi_fila (fila);

/* Insere um projetil na fila */
void enqueue (fila, projetil);

/* Remove e retorna o primeiro elemento da fila */
projetil dequeue (fila);
