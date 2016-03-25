#include <stdio.h>
#include <math.h>

typedef struct {
  double i, j;
  // respectivamente as componentes horizontais e verticais
  // da força que age sobre o corpo
} forca;

forca atracao (double xa, double ya, double ma, double xb, double yb, double mb){

  forca res;
  double g = (6,67408) / pow(10, 11;)
  double dist, ft;
  double dx = xa - xb;
  double dy = ya - yb;

  dist = pow(dx, 2) + pow(dy, 2);
  dist = sqrt(dist);
  
  ft = (g * ma * mb) / pow(dist, 2);
  res->i = ft * (sqrt(pow(dx, 2)) / dist);
  res->j = ft * (sqrt(pow(dy, 2)) / dist);

  return res;
}

forca result (forca a, forca b){
  
  forca re;

  re->i = a->i + b->i;
  re->j = a->j + b->j;

  return re;
}

double velocidade (forca aplicada, double massa, double t, double vi){
  double velres, forc;

  forc = sqrt(pow(aplicada->i, 2) + pow(aplicada->j, 2));

  velres = (forc * t) / massa;
  velres += vi;

  return velres;
}
