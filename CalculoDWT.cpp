#include <stdio.h>
#include <stdlib.h>
#include "CalculoDWT.h"
#include "Pixel.h"

/* Paso alto multiplicar por 2 */

float __inline **malloc_2d_f(int ancho, int alto) {
  float **p = (float **) malloc(alto * sizeof(float *));
  for (int j = 0; j < alto; j++)
    p[j] = (float *) malloc(ancho * sizeof(float));
  return p;
}

void __inline free_2d_f(int ancho, int alto, float **p) {
  for (int j = 0; j < alto; j++)
    free(p[j]);
  free(p);
}

int __inline **malloc_2d(int ancho, int alto) {
  int **p = (int **) malloc(alto * sizeof(int *));
  for (int j = 0; j < alto; j++)
    p[j] = (int *) malloc(ancho * sizeof(int));
  return p;
}

void __inline free_2d(int ancho, int alto, int **p) {
  for (int j = 0; j < alto; j++)
    free(p[j]);
  free(p);
}

void trasponer_matriz(int ancho, int alto, float **M, float **Mt) {
  for (int y = 0; y < alto; y++) {
    for (int x = 0; x < ancho; x++) {
      Mt[x][y] = M[y][x];
    }
  }
}

void trasponer_matriz(int ancho, int alto, int **M, int **Mt) {
  for (int y = 0; y < alto; y++) {
    for (int x = 0; x < ancho; x++) {
      Mt[x][y] = M[y][x];
    }
  }
}

float aplica_kernel_f(int x, int y, int ancho, float *comp, bool es_par, bool inverso = false) {
  float po = comp[x];
  float p[2];
  if (inverso == false) {
    if (es_par) { // Es paso bajo!
      po *= pbf[0];
      for (int j = 1; j < 5; j++) {
        if (x - j < 0)
          p[0] = comp[x + j];
        else
          p[0] = comp[x - j];
        if (x + j >= ancho)
          p[1] = comp[x - j];
        else
          p[1] = comp[x + j];
        po += p[0] * pbf[j] + p[1] * pbf[j];
      }
    } else { // No es par... Es pasa alto!
      po *= paf[0];
      for (int j = 1; j < 4; j++) {
        if (x - j < 0)
          p[0] = comp[x + j];
        else
          p[0] = comp[x - j];
        if (x + j >= ancho)
          p[1] = comp[x - j];
        else
          p[1] = comp[x + j];
        po += p[0] * paf[j] + p[1] * paf[j];
      }
    }
  }
  else {
    if (!es_par) { // Es paso bajo!
      po *= pbf_i[0];
      for (int j = 1; j < 4; j++) {
        if (x - j < 0)
          p[0] = comp[x + j];
        else
          p[0] = comp[x - j];
        if (x + j >= ancho)
          p[1] = comp[x - j];
        else
          p[1] = comp[x + j];
        po += p[0] * pbf_i[j] + p[1] * pbf_i[j];
      }
    } else { // No es par... Es pasa alto!
      po *= paf_i[0];
      for (int j = 1; j < 5; j++) {
        if (x - j < 0)
          p[0] = comp[x + j];
        else
          p[0] = comp[x - j];
        if (x + j >= ancho)
          p[1] = comp[x - j];
        else
          p[1] = comp[x + j];
        po += p[0] * paf_i[j] + p[1] * paf_i[j];
      }
    }
  }
  return po;
}

float aplica_kernel(int x, int y, int ancho, int *comp, bool es_par, bool inverso = false) {
  int po = comp[x];
  int p[2];
  if (inverso == false) {
    if (es_par) { // Es paso bajo!
      po *= pb[0];
      for (int j = 1; j < 3; j++) {
        if (x - j < 0)
          p[0] = comp[x + j];
        else
          p[0] = comp[x - j];
        if (x + j >= ancho)
          p[1] = comp[x - j];
        else
          p[1] = comp[x + j];
        po += p[0] * pb[j] + p[1] * pb[j];
      }
    } else { // No es par... Es pasa alto!
      po *= pa[0];
      // j == 1
      if (x - 1 < 0)
        p[0] = comp[x + 1];
      else
        p[0] = comp[x - 1];
      if (x + 1 >= ancho)
        p[1] = comp[x - 1];
      else
        p[1] = comp[x + 1];
      po += p[0] * pa[1] + p[1] * pa[1];
    }
  }
  else {
    if (!es_par) { // Es paso bajo!
      po *= pb_i[0];
      // j == 1
      if (x - 1 < 0)
        p[0] = comp[x + 1];
      else
        p[0] = comp[x - 1];
      if (x + 1 >= ancho)
        p[1] = comp[x - 1];
      else
        p[1] = comp[x + 1];
      po += p[0] * pb_i[1] + p[1] * pb_i[1];
    } else { // No es par... Es pasa alto!
      po *= pa_i[0];
      for (int j = 1; j < 3; j++) {
        if (x - j < 0)
          p[0] = comp[x + j];
        else
          p[0] = comp[x - j];
        if (x + j >= ancho)
          p[1] = comp[x - j];
        else
          p[1] = comp[x + j];
        po += p[0] * pa_i[j] + p[1] * pa_i[j];
      }
    }
  }
  return po;
}


void DWT_f_filas(int ancho, int alto, float **Y420, float **Cb420, float **Cr420) {
  float **_Y420 = malloc_2d_f(ancho, alto);
  float **_Cb420 = malloc_2d_f(ancho/2, alto/2);
  float **_Cr420 = malloc_2d_f(ancho/2, alto/2);

  // llamada a aplica_kernel por cada elemento
  for (int y = 0; y < alto; y++) {
    for (int x = 0; x < ancho; x++) {
      _Y420[y][x] = aplica_kernel_f(x, y, ancho, Y420[y], (x % 2) == 0);
      if (y < (alto/2) && x < (ancho/2)) {
        _Cb420[y][x] = aplica_kernel_f(x, y, ancho/2, Cb420[y], (x % 2) == 0);
        _Cr420[y][x] = aplica_kernel_f(x, y, ancho/2, Cr420[y], (x % 2) == 0);
      }
    }
  }
  // guardar los resultados en el orden correcto
  for (int y = 0; y < alto; y++) {
    for (int x = 0; x < ancho; x++) {
      if (x % 2 == 0) { // es par => resultado del paso bajo
        Y420[y][x/2] = _Y420[y][x];
        if (y < (alto/2) && x < (ancho/2)) {
          Cb420[y][x/2] = _Cb420[y][x];
          Cr420[y][x/2] = _Cr420[y][x];
        }
      }
      else { // es impar => resultado del paso alto
         Y420[y][x/2 + ancho/2] = _Y420[y][x] * 2.0;
        if (y < (alto/2) && x < (ancho/2)) {
          int ancho_2 = ancho/2;
          Cb420[y][x/2 + ancho_2/2] = _Cb420[y][x] * 2.0;
          Cr420[y][x/2 + ancho_2/2] = _Cr420[y][x] * 2.0;
        }
      }
    }
  }
  free_2d_f(ancho, alto, _Y420);
  free_2d_f(ancho/2, alto/2, _Cb420);
  free_2d_f(ancho/2, alto/2, _Cr420);
  
  /* TEST
  float Muestras[32]= {33,21,22,11,35,34,33,64,66,44,33,64,34,12,55,43,33,21,22,11,35,34,33,64,66,44,33,64,34,12,55,43};
  float tmp[32];
  for (int i=0; i<32; i++) {
    tmp[i] = aplica_kernel_f(i, 1, 32, Muestras, (i % 2) == 0);
  }
  for (int i=0; i<32; i++) {
    if (i % 2 == 0)
      Muestras[i/2] = tmp[i];
    else
      Muestras[i/2+16] = tmp[i]*2.0;
  }
  
  for (int i=0; i<32; i++) {
    if (i % 2 == 0)
      tmp[i] = Muestras[i/2]*2.0;
    else
      tmp[i] = Muestras[i/2+16]; 
  }
  
  for (int i=0; i<32; i++) {
    Muestras[i] = aplica_kernel_f(i, 1, 32, tmp, (i % 2) == 0, true);
  }
  
  for (int i=0; i<32; i++)
    printf("Resultado %i : %.2f \n", i+1, Muestras[i]);*/
}

void DWT_f_filas_i(int ancho, int alto, float **Y420, float **Cb420, float **Cr420) {
  float **_Y420 = malloc_2d_f(ancho, alto);
  float **_Cb420 = malloc_2d_f(ancho/2, alto/2);
  float **_Cr420 = malloc_2d_f(ancho/2, alto/2);
  
  // reorganizar el orden de los elementos
  for (int y = 0; y < alto; y++) {
    for (int x = 0; x < ancho; x++) {
      if (x % 2 == 0) { // es par => resultado del paso bajo
        _Y420[y][x] = Y420[y][x/2] * 2.0;
        if (y < (alto/2) && x < (ancho/2)) {
          _Cb420[y][x] = Cb420[y][x/2] * 2.0;
          _Cr420[y][x] = Cr420[y][x/2]* 2.0;
        }
      }
      else { // es impar => resultado del paso alto
          _Y420[y][x] = Y420[y][x/2 + ancho/2];
        if (y < (alto/2) && x < (ancho/2)) {
          int ancho_2 = ancho/2;
          _Cb420[y][x] = Cb420[y][x/2 + ancho_2/2];
          _Cr420[y][x] = Cr420[y][x/2 + ancho_2/2];
        }
      }
    }
  }
  
  // llamada a aplica_kernel (inverso) por cada elemento
  for (int y = 0; y < alto; y++) {
    for (int x = 0; x < ancho; x++) {
        Y420[y][x] = aplica_kernel_f(x, y, ancho, _Y420[y], (x % 2) == 0, true);
      if (y < (alto/2) && x < (ancho/2)) {
        Cb420[y][x] = aplica_kernel_f(x, y, ancho/2, _Cb420[y], (x % 2) == 0, true);
        Cr420[y][x] = aplica_kernel_f(x, y, ancho/2, _Cr420[y], (x % 2) == 0, true);
      }
    }
  }
  free_2d_f(ancho, alto, _Y420);
  free_2d_f(ancho/2, alto/2, _Cb420);
  free_2d_f(ancho/2, alto/2, _Cr420);
}

void DWT_f_columnas(int ancho, int alto, float **Y420, float **Cb420, float **Cr420) {
  float **_Y420 = malloc_2d_f(alto, ancho);
  float **_Cb420 = malloc_2d_f(alto/2, ancho/2);
  float **_Cr420 = malloc_2d_f(alto/2, ancho/2);
  
  // trasponer matrices
  trasponer_matriz(ancho, alto, Y420, _Y420);
  trasponer_matriz(ancho, alto, Cb420, _Cb420);
  trasponer_matriz(ancho, alto, Cr420, _Cr420);
  
  DWT_f_filas(alto, ancho, _Y420, _Cb420, _Cr420);
  
  // retrasponer matrices
  trasponer_matriz(alto, ancho, _Y420, Y420);
  trasponer_matriz(alto, ancho, _Cb420, Cb420);
  trasponer_matriz(alto, ancho, _Cr420, Cr420);
  
  free_2d_f(alto, ancho, _Y420);
  free_2d_f(alto/2, ancho/2, _Cb420);
  free_2d_f(alto/2, ancho/2, _Cr420);
}

void DWT_f_columnas_i(int ancho, int alto, float **Y420, float **Cb420, float **Cr420) {
  float **_Y420 = malloc_2d_f(alto, ancho);
  float **_Cb420 = malloc_2d_f(alto/2, ancho/2);
  float **_Cr420 = malloc_2d_f(alto/2, ancho/2);
  
  // trasponer matrices
  trasponer_matriz(ancho, alto, Y420, _Y420);
  trasponer_matriz(ancho, alto, Cb420, _Cb420);
  trasponer_matriz(ancho, alto, Cr420, _Cr420);
  
  DWT_f_filas_i(alto, ancho, _Y420, _Cb420, _Cr420);
  
  // retrasponer matrices
  trasponer_matriz(alto, ancho, _Y420, Y420);
  trasponer_matriz(alto, ancho, _Cb420, Cb420);
  trasponer_matriz(alto, ancho, _Cr420, Cr420);
  
  free_2d_f(alto, ancho, _Y420);
  free_2d_f(alto/2, ancho/2, _Cb420);
  free_2d_f(alto/2, ancho/2, _Cr420);
}


void DWT_filas(int ancho, int alto, int **Y420, int **Cb420, int **Cr420) {
  int **_Y420 = malloc_2d(ancho, alto);
  int **_Cb420 = malloc_2d(ancho/2, alto/2);
  int **_Cr420 = malloc_2d(ancho/2, alto/2);
  
  // llamada a aplica_kernel por cada elemento
  for (int y = 0; y < alto; y++) {
    for (int x = 0; x < ancho; x++) {
      _Y420[y][x] = aplica_kernel(x, y, ancho, Y420[y], (x % 2) == 0);
      if (y < (alto/2) && x < (ancho/2)) {
        _Cb420[y][x] = aplica_kernel(x, y, ancho/2, Cb420[y], (x % 2) == 0);
        _Cr420[y][x] = aplica_kernel(x, y, ancho/2, Cr420[y], (x % 2) == 0);
      }
    }
  }
  // guardar los resultados en el orden correcto
  for (int y = 0; y < alto; y++) {
    for (int x = 0; x < ancho; x++) {
      if (x % 2 == 0) { // es par => resultado del paso bajo
        Y420[y][x/2] = _Y420[y][x];
        if (y < (alto/2) && x < (ancho/2)) {
          Cb420[y][x/2] = _Cb420[y][x];
          Cr420[y][x/2] = _Cr420[y][x];
        }
      }
      else { // es impar => resultado del paso alto
        Y420[y][x/2 + ancho/2] = _Y420[y][x];
        if (y < (alto/2) && x < (ancho/2)) {
          int ancho_2 = ancho/2;
          Cb420[y][x/2 + ancho_2/2] = _Cb420[y][x];
          Cr420[y][x/2 + ancho_2/2] = _Cr420[y][x];
        }
      }
    }
  }
  free_2d(ancho, alto, _Y420);
  free_2d(ancho/2, alto/2, _Cb420);
  free_2d(ancho/2, alto/2, _Cr420);
}

void DWT_filas_i(int ancho, int alto, int **Y420, int **Cb420, int **Cr420) {
  int **_Y420 = malloc_2d(ancho, alto);
  int **_Cb420 = malloc_2d(ancho/2, alto/2);
  int **_Cr420 = malloc_2d(ancho/2, alto/2);
  
  // reorganizar el orden de los elementos
  for (int y = 0; y < alto; y++) {
    for (int x = 0; x < ancho; x++) {
      if (x % 2 == 0) { // es par => resultado del paso bajo
        _Y420[y][x] = Y420[y][x/2];
        if (y < (alto/2) && x < (ancho/2)) {
          _Cb420[y][x] = Cb420[y][x/2];
          _Cr420[y][x] = Cr420[y][x/2];
        }
      }
      else { // es impar => resultado del paso alto
        _Y420[y][x] = Y420[y][x/2 + ancho/2];
        if (y < (alto/2) && x < (ancho/2)) {
          int ancho_2 = ancho/2;
          _Cb420[y][x] = Cb420[y][x/2 + ancho_2/2];
          _Cr420[y][x] = Cr420[y][x/2 + ancho_2/2];
        }
      }
    }
  }
  
  // llamada a aplica_kernel (inverso) por cada elemento
  for (int y = 0; y < alto; y++) {
    for (int x = 0; x < ancho; x++) {
      Y420[y][x] = aplica_kernel(x, y, ancho, _Y420[y], (x % 2) == 0, true);
      if (y < (alto/2) && x < (ancho/2)) {
        Cb420[y][x] = aplica_kernel(x, y, ancho/2, _Cb420[y], (x % 2) == 0, true);
        Cr420[y][x] = aplica_kernel(x, y, ancho/2, _Cr420[y], (x % 2) == 0, true);
      }
    }
  }
  free_2d(ancho, alto, _Y420);
  free_2d(ancho/2, alto/2, _Cb420);
  free_2d(ancho/2, alto/2, _Cr420);
}

void ConversionYCbCr420aDWT(int ancho, int alto, float **Y420, float **Cb420, float **Cr420) {
  DWT_f_filas(ancho, alto, Y420, Cb420, Cr420);
}

void ConversionDWTaYCbCr420(int ancho, int alto, float **Y420, float **Cb420, float **Cr420) {
  DWT_f_filas_i(ancho, alto, Y420, Cb420, Cr420);
}

void ConversionYCbCr42iaDWi(int ancho, int alto, int **Y420, int **Cb420, int **Cr420) {
  DWT_filas(ancho, alto, Y420, Cb420, Cr420);
}

void ConversionDWiaYCbCr42i(int ancho, int alto, int **Y420, int **Cb420, int **Cr420) {
  DWT_filas_i(ancho, alto, Y420, Cb420, Cr420);
}

