typedef struct {
  double i, j;
} forca;

forca atracao (double xa, double ya, double ma, double xb, double yb, double mb);

forca result (forca a, forca b);

void velocidade (forca aplicada, double massa, double t, double *vh, double *vv);

