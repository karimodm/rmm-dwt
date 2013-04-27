#ifndef RGBYCbCr_H
#define RGBYCbCr_H

void ConversionRGBaYCbCr444(int ancho, int alto, unsigned char **R, unsigned char **G, unsigned char **B,
                            unsigned char **Y, signed char **Cb, signed char **Cr);


void ConversionYCbCr444aRGB(int ancho, int alto, unsigned char **Y, signed char **Cb, signed char **Cr,
                            unsigned char **R, unsigned char **G, unsigned char **B);

void ConversionYCbCr444aYCbCr420(int ancho, int alto, signed char **Cb444, signed char **Cr444,
                                 signed char **Cb420, signed char **Cr420);


void ConversionYCbCr420aYCbCr444(int ancho, int alto, signed char **Cb420, signed char **Cr420,
                                 signed char **Cb444, signed char **Cr444);

#endif
