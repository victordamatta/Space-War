int reduz_coordenada (double x) {
    return (int) x * (400/(1.2e7)) + 400;
}

double amplia_distancia (int x) {
    return x * ((1.2e7)/400);
}
