#include <stdio.h>
#include <stdlib.h>
#include "CalculoDWT.h"
#include "Pixel.h"

/* Paso alto multiplicar por 2 */

float __inline **malloc_2d(int ancho, int alto) {
  float **p = (float **) malloc(alto * sizeof(float *));
  for (int j = 0; j < alto; j++)
    p[j] = (float *) malloc(ancho * sizeof(float));
  return p;
}

Pixel &aplica_kernel_f(int x, int y, float *Y420, float *Cb420, float *Cr420, bool es_par, bool inverso = false) {
  Pixel po(Y420[x], Cr420[x], Cb420[x]);
  Pixel p[2];
  if (es_par) { /* Es paso bajo! */
    po *= pbf[0];
    for (int j = 1; j < 5; j++) {
       if (x - j < 0)
          p[0].set(Y420[x + j], Cb420[x + j], Cr420[x + j];
       else
          p[0].set(Y420[x - j], Cb420[x - j], Cr420[x - j];
       if (x + j > ancho)
          p[1].set(Y420[x - j], Cb420[x - j], Cr420[x - j];
       else
          p[1].set(Y420[x + j], Cb420[x + j], Cr420[x + j];
       po += p[0] * pbf[j] + p[1] * pbf[j];
    }
  } else { /* No es par... Es pasa alto! */
    po *= paf[0];
    for (int j = 0; j < 4; j++) {
       if (x - j < 0)
          p[0].set(Y420[x + j], Cb420[x + j], Cr420[x + j];
       else
          p[0].set(Y420[x - j], Cb420[x - j], Cr420[x - j];
       if (x + j > ancho)
          p[1].set(Y420[x - j], Cb420[x - j], Cr420[x - j];
       else
          p[1].set(Y420[x + j], Cb420[x + j], Cr420[x + j];
       po += p[0] * paf[j] + p[1] * paf[j];
    }
  }
  return po;
}

void DWT_f_filas(int ancho, int alto, float **Y420, float **Cb420, float **Cr420) {
	float **_Y420 = malloc_2d(ancho, alto);
	float **_Cr420 = malloc_2d(ancho, alto);
	float **_Cb420 = malloc_2d(ancho, alto);
	Pixel p;
	for (int y = 0; y < alto; y++)
	  for (int x = 0; x < ancho; x++) {
	    p = aplica_kernel_f(x, y, Y420[y], Cr420[y], Cb420[y], (x % 2) == 0);
	    _Y420[y][x]  = p.Y;
	    _Cb420[y][x] = p.Cb;
	    _Cr420[y][x] = p.Cr;
	  }
}
//void DWT_f_columnas

void ConversionYCbCr420aDWT(int ancho, int alto, float **Y420, float **Cb420, float **Cr420) {
	
}


