#include "RGBYCbCr.h"

// matriz para la conversion RGB a YCbCr

const double RY = (77.0/256.0),  GY = (150.0/256.0),  BY = (29.0/256.0);
const double RCb = (-44.0/256.0), GCb = (-87.0/256.0),  BCb = (131.0/256.0);
const double RCr = (131.0/256.0), GCr = (-110.0/256.0), BCr = (-21.0/256.0);

void ConversionRGBaYCbCr444(int ancho, int alto, unsigned char **R, unsigned char **G, unsigned char **B, 
							                     unsigned char **Y, signed char **Cb, signed char **Cr)
{
  // COMPLETAR
  for (int al=0; al<alto; al++) {
    for (int an=0; an<ancho; an++) {
      Y[al][an] = RY*R[al][an] + GY*G[al][an] + BY*B[al][an];
      Cb[al][an] = RCb*R[al][an] + GCb*G[al][an] + BCb*B[al][an];
      Cr[al][an] = RCr*R[al][an] + GCr*G[al][an] + BCr*B[al][an];
    }
  }

}

// matriz para la conversion YCbCr a RGB

const double iRY = (1), iRCb = (-40.0/16237.0),   iRCr = (22173.0/16237.0);
const double iGY = (1), iGCb = (-5416.0/16237.0), iGCr = (-11363.0/16237.0);
const double iBY = (1), iBCb = (28120.0/16237.0), iBCr = (-99.0/16237.0);

void ConversionYCbCr444aRGB(int ancho, int alto, unsigned char **Y, signed char **Cb, signed char **Cr, 
							                     unsigned char **R, unsigned char **G, unsigned char **B)
{
  // COMPLETAR
  for (int al=0; al<alto; al++) {
    for (int an=0; an<ancho; an++) {
      R[al][an] = iRY*Y[al][an] + iRCb*Cb[al][an] + iRCr*Cr[al][an];
      G[al][an] = iGY*Y[al][an] + iGCb*Cb[al][an] + iGCr*Cr[al][an];
      B[al][an] = iBY*Y[al][an] + iBCb*Cb[al][an] + iBCr*Cr[al][an];
    }
  }
}

void ConversionYCbCr444aYCbCr420(int ancho, int alto, signed char **Cb444, signed char **Cr444, 
							                          signed char **Cb420, signed char **Cr420)
{
  // COMPLETAR
  for (int al=0; al<alto/2; al++) {
    for (int an=0; an<ancho/2; an++) {
      Cb420[al][an] = Cb444[2*al][2*an];
      Cr420[al][an] = Cr444[2*al][2*an];
    }
  }

}

void ConversionYCbCr420aYCbCr444(int ancho, int alto, signed char **Cb420, signed char **Cr420,
								                      signed char **Cb444, signed char **Cr444)
{
  // COMPLETAR
  for (int al=0; al<alto/2; al++) {
    for (int an=0; an<ancho/2; an++) {
      Cb444[2*al][2*an] = Cb420[al][an];
      Cb444[2*al+1][2*an] = Cb420[al][an];
      Cb444[2*al][2*an+1] = Cb420[al][an];
      Cb444[2*al+1][2*an+1] = Cb420[al][an];
    }
  }

}
