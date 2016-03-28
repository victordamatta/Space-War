#include <stdio.h>
#include <math.h>

typedef struct {
  double i, j;
  // respectivamente as componentes horizontais e verticais
  // da força que age sobre o corpo
} forca;

forca atracao (double xa, double ya, double ma, double xb, double yb, double mb){

  forca res;
  double g = (6.67408);
  double dist, ft;
  double dx = xb - xa;
  double dy = yb - ya;

  dist = pow(dx, 2) + pow(dy, 2);
  dist = sqrt(dist);
  
  ft = (g * ma * mb) / pow(dist, 2);
  ft = ft / pow(10, 11);
  res.i = ft * (dx / dist);
  res.j = ft * (dy / dist);

  return res;
}

forca result (forca a, forca b){
  
  forca re;

  re.i = a.i + b.i;
  re.j = a.j + b.j;

  return re;
}

// A função atração retorna o valor das componentes da força de atração do corpo B sobre o corpo A, 
// ou seja, o valor das componentes da força que age sobre o corpo A

void velocidade (forca aplicada, double massa, double t, double *vh, double *vv){

  *vh += (aplicada.i * t) / massa;
  *vv += (aplicada.j * t) / massa;

}

// vh e vv sao respectivamente as componentes horizontais e verticais da velocidade

int main (){
  forca ap, teste;

  forca atrac = atracao(1, 2, 7000000, 5, 5, 8000000);
  // A esta em (1,2) e tem M = 7000000, e B esta em (5,5) e tem M = 8000000
  // Devolve a força que age em A
  forca atra = atracao(5, 5, 8000000, 1, 2, 7000000);
  // Devolve a força que age em B

  double vh = 1, vv = 3;
  ap.i = 2;
  ap.j = 3;
  velocidade (ap, 3, 10, &vh, &vv);
  teste = result (atrac, atra);
  printf ("As componentes deveriam ser zero : i = %f \t j = %f\n", teste.i, teste.j);
  teste = result (atrac, ap);
  printf ("Soma de atrac e ap : i = %f \t j = %f\n", teste.i, teste.j);
  // i = 121.599514      j = 92.699635
  printf ("\n Componentes do Vetor que age sobre A atraindo ele a B : i = %f \t j = %f \n", atrac.i, atrac.j);
  // i = 119.599514 e j = 89.699635 
  printf ("\n Componentes do Vetor que age sobre B atraindo ele a A : i = %f \t j = %f \n", atra.i, atra.j);
  // i = -119.599514 e j = -89.699635 
  printf ("\nComponentes da velocidade após a aplicação da força : Vh = %f \t Vv = %f\n", vh, vv);
  // devia imprimir 7.666667 e 13.000000

  return 0;
}
