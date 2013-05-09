#ifndef CALCULODWT_H
#define CALCULODWT_H

const float pbf[5] = { 0.602949018236360, 0.266864118442875, -0.078223266528990, -0.016864118442875, 0.026748757410810 };
const float paf[4] = { 1.115087052457000, -0.591271763114250, -0.057543526228500, 0.091271763114250 };
//const float paf[4] = { 0.557543526228500, -0.295635881557125, -0.028771763114250, 0.045635881557125 };

const float pbf_i[4] = { 1.115087052457000, 0.591271763114250, -0.057543526228500, -0.091271763114250 };
//const float pbf_i[4] = { 0.557543526228500, 0.295635881557125, -0.028771763114250, -0.045635881557125 };
const float paf_i[5] = { 0.602949018236360, -0.266864118442875, -0.078223266528990, 0.016864118442875, 0.026748757410810 };

const float pb[3] = { 0.75, 0.25, -0.125 };
const float pa[2] = { 1.0, 0.5};

const float pb_i[2] = { 1.0, -0.5 };
const float pa_i[3] = { 0.75, -0.25, -0.125};

void DWT_f_filas(int ancho, int alto, float **Y420, float **Cb420, float **Cr420);
void DWT_f_filas_i(int ancho, int alto, float **Y420, float **Cb420, float **Cr420);
void DWT_f_columnas();

void DWT_filas(int ancho, int alto, int **Y420, int **Cb420, int **Cr420);
void DWT_filas_i(int ancho, int alto, int **Y420, int **Cb420, int **Cr420);

void ConversionYCbCr420aDWT(int ancho, int alto, float **Y420, float **Cb420, float **Cr420);
void ConversionDWTaYCbCr420(int ancho, int alto, float **Y420, float **Cb420, float **Cr420);
void ConversionYCbCr42iaDWi(int ancho, int alto, int **Y420, int **Cb420, int **Cr420);
void ConversionDWiaYCbCr42i(int ancho, int alto, int **Y420, int **Cb420, int **Cr420);

#endif
