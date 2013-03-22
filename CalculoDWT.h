#ifndef CALCULODWT_H
#define CALCULODWT_H

const float pbf[5] = { 0.602949018236360, 0.266864118442875, -0.078223266528990, -0.016864118442875, 0.026748757410810 };
const float paf[4] = { 0.557543526228500, -0.295635881557125, -0.028771763114250, 0.045635881557125 };

const float pbf_i[4] = { 0.557543526228500, 0.295635881557125, -0.028771763114250, -0.045635881557125 };
const float paf_i[5] = { 0.602949018236360, -0.266864118442875, -0.078223266528990, 0.016864118442875, 0.026748757410810 };

void DWT_f_filas(int ancho, int alto, float **Y420, float **Cb420, float **Cr420);
void DWT_f_columnas();

void ConversionYCbCr420aDWT(int ancho, int alto, float **Y420, float **Cb420, float **Cr420);

#endif
