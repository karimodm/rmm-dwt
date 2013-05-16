/*
 * PRACTICAS REDES MULTIMEDIA
 *
 * COMPRESION JPEG2000 - DWT/IDWT
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ImagenES.h"
#include "CalculoDWT.h"

#define YCbCr420aDWT 1
#define DWTaYCbCr420 2
#define YCbCr42iaDWi 3
#define DWiaYCbCr42i 4

#define YCbCr420 1
#define DWT 2
#define YCbCr42i 3
#define DWi 4
#define NO_EXT 5
#define UNKNOWN 6

static char *ficheroDWTPorDefecto="lena.DWT";
//static char *fichero444PorDefecto="lena.444";
static char *fichero420PorDefecto="lena.420";
static int opcionPorDefecto=YCbCr420aDWT;
static int anchoPorDefecto=512;
static int altoPorDefecto=512;

static char *ficheroEntrada=fichero420PorDefecto;
static char *ficheroSalida=ficheroDWTPorDefecto;
static int opcion=opcionPorDefecto;
static int ancho=anchoPorDefecto;
static int alto=altoPorDefecto;

#define Mayusculas(x) ((x>='a' && x<='z')?x+('A'-'a'):x)

int DeterminaTipo(char *Nombre)
{
  int f=0;

  while (Nombre[f]!=0) f++;  
  while (Nombre[f]!='.' && f>0) f--; 
  if (!f++) 
    return NO_EXT;
  else if (Mayusculas(Nombre[f])=='4' && Mayusculas(Nombre[f+1])=='2' && Mayusculas(Nombre[f+2])=='0')
    return YCbCr420;
  else if (Mayusculas(Nombre[f])=='D' && Mayusculas(Nombre[f+1])=='W' && Mayusculas(Nombre[f+2])=='T')
    return DWT;
  else if (Mayusculas(Nombre[f])=='4' && Mayusculas(Nombre[f+1])=='2' && Mayusculas(Nombre[f+2])=='I')
    return YCbCr42i;
  else if (Mayusculas(Nombre[f])=='D' && Mayusculas(Nombre[f+1])=='W' && Mayusculas(Nombre[f+2])=='I')
    return DWi;
  else 
    return UNKNOWN;
}

void ProcesaArgumentos(int argc, char **argv)
{
  if (argc>=2)
  {
    if (argc!=7 || strcmp(argv[1],"-i") || strcmp(argv[3],"-o") || atoi(argv[5])==0 || atoi(argv[6])==0)
    { 
      printf("\nTeclea \"-i ImagenFte.xxx -o ImagenDest.yyy ancho alto\"\n"); 
      exit(1); 
    }
    ancho=atoi(argv[5]);
    alto=atoi(argv[6]); 
    ficheroEntrada=argv[2];
    ficheroSalida=argv[4];
    if (DeterminaTipo(ficheroEntrada)==YCbCr420 && DeterminaTipo(ficheroSalida)==DWT)
      opcion=YCbCr420aDWT;
    else if (DeterminaTipo(ficheroEntrada)==DWT && DeterminaTipo(ficheroSalida)==YCbCr420)
      opcion=DWTaYCbCr420;
    else if (DeterminaTipo(ficheroEntrada)==YCbCr42i && DeterminaTipo(ficheroSalida)==DWi)
      opcion=YCbCr42iaDWi;
    else if (DeterminaTipo(ficheroEntrada)==DWi && DeterminaTipo(ficheroSalida)==YCbCr42i)
      opcion=DWiaYCbCr42i;
    else if (DeterminaTipo(ficheroEntrada)==YCbCr420 && DeterminaTipo(ficheroSalida)==YCbCr420)
      PRUEBA();
    else
    {
      printf("\nConversion no implementada (comprueba las extensiones)\n"); 
      exit(1); 
    }
  }
}

long double CalculaMSE(float **Y1, float **Y2, int ancho, int alto)
{
	// COMPLETAR
  long double res = 0.0;
  
  for (int al=0; al<alto; al++) {
    for (int an=0; an<ancho; an++) {
      long double _Y1 = (long double)Y1[al][an];
      long double _Y2 = (long double)Y2[al][an];
      res += ((_Y1-_Y2)*(_Y1-_Y2));
    }
  }
  res /= (long double)(ancho*alto);
  
  return res;
}

void PRUEBA() {
  float **Y420, **Cb420, **Cr420;
  
  ReservaPlano(ancho, alto, &Y420);
  ReservaPlano(ancho/2, alto/2, &Cb420);
  ReservaPlano(ancho/2, alto/2, &Cr420);
  
  float **Y420_2, **Cb420_2, **Cr420_2;
  
  ReservaPlano(ancho, alto, &Y420_2);
  ReservaPlano(ancho/2, alto/2, &Cb420_2);
  ReservaPlano(ancho/2, alto/2, &Cr420_2);
  
  if (CargaYCbCr420(ficheroEntrada, ancho, alto, Y420, Cb420, Cr420) != 0)
  {
    printf("Error al leer fichero\n");
    exit(1);
  }
  if (CargaYCbCr420(ficheroSalida, ancho, alto, Y420_2, Cb420_2, Cr420_2) != 0)
  {
    printf("Error al leer fichero\n");
    exit(1);
  }
  
  printf("%.50Lf \n", CalculaMSE(Y420, Y420_2, ancho, alto));
  printf("%.50Lf \n", CalculaMSE(Cb420, Cb420_2, ancho/2, alto/2));
  printf("%.50Lf \n", CalculaMSE(Cr420, Cr420_2, ancho/2, alto/2));
  
  exit(-1);
}


int main(int argc, char **argv)
{
  printf("\n--------------------------------\n");
  printf("PRACTICAS REDES MULTIMEDIA (RMM)\n");
  printf("Facultad de Informatica, UPV\n");
  printf("--------------------------------\n");
  printf("JPEG2000 - DWT/IDWT\n");
  printf("--------------------------------\n");
  
  ProcesaArgumentos(argc,argv);

  if (opcion==YCbCr420aDWT || opcion==DWTaYCbCr420)
  { // CONVERSION DE .420 A .DWT (FLOAT) o CONVERSION DE .DWT A .420 (FLOAT)
    float **Y420, **Cb420, **Cr420;
    
    ReservaPlano(ancho, alto, &Y420);
    ReservaPlano(ancho/2, alto/2, &Cb420);
    ReservaPlano(ancho/2, alto/2, &Cr420);
    
    if (opcion==YCbCr420aDWT)
    { // CONVERSION DE .420 A .DWT (FLOAT)
      if (CargaYCbCr420(ficheroEntrada, ancho, alto, Y420, Cb420, Cr420) != 0)
      {
        printf("Error al leer fichero\n");
        exit(1);
      }
      
      ConversionYCbCr420aDWT(ancho, alto, Y420, Cb420, Cr420);
      if (GuardaDWT420(ficheroSalida, ancho, alto, Y420, Cb420, Cr420) != 0)
      {
        printf("Error al escribir fichero\n");
        exit(1);
      }
    }
    else
    { // CONVERSION DE .DWT A .420 (FLOAT)
      if (CargaDWT420(ficheroEntrada, ancho, alto, Y420, Cb420, Cr420) != 0)
      {
        printf("Error al leer fichero\n");
        exit(1);
      }
      ConversionDWTaYCbCr420(ancho, alto, Y420, Cb420, Cr420);
      if (GuardaYCbCr420(ficheroSalida, ancho, alto, Y420, Cb420, Cr420) != 0)
      {
        printf("Error al escribir fichero\n");
        exit(1);
      }
    }
    
    LiberaPlano(ancho, alto, &Y420);
    LiberaPlano(ancho/2, alto/2, &Cb420);
    LiberaPlano(ancho/2, alto/2, &Cr420);
  }
  else
  { // CONVERSION DE .42i A .DWi (ENTERO) o CONVERSION DE .DWi A .42i (ENTERO)
    int **Y42i, **Cb42i, **Cr42i;
    
    ReservaPlano(ancho, alto, &Y42i);
    ReservaPlano(ancho/2, alto/2, &Cb42i);
    ReservaPlano(ancho/2, alto/2, &Cr42i);
    
    if (opcion==YCbCr42iaDWi)
    { // CONVERSION DE .42i A .DWi (ENTERO)
      if (CargaDWT420q(ficheroEntrada, ancho, alto, Y42i, Cb42i, Cr42i) != 0)
      {
        printf("Error al leer fichero\n");
        exit(1);
      }
      ConversionYCbCr42iaDWi(ancho, alto, Y42i, Cb42i, Cr42i);
      if (GuardaDWT420q(ficheroSalida, ancho, alto, Y42i, Cb42i, Cr42i) != 0)
      {
        printf("Error al escribir fichero\n");
        exit(1);
      }
    }
    else
    { // CONVERSION DE .DWi A .42i (ENTERO)
      if (CargaDWT420q(ficheroEntrada, ancho, alto, Y42i, Cb42i, Cr42i) != 0)
      {
        printf("Error al leer fichero\n");
        exit(1);
      }
      ConversionDWiaYCbCr42i(ancho, alto, Y42i, Cb42i, Cr42i);
      if (GuardaDWT420q(ficheroSalida, ancho, alto, Y42i, Cb42i, Cr42i) != 0)
      {
        printf("Error al escribir fichero\n");
        exit(1);
      }
    }
    LiberaPlano(ancho, alto, &Y42i);
    LiberaPlano(ancho/2, alto/2, &Cb42i);
    LiberaPlano(ancho/2, alto/2, &Cr42i);
  }
  return 0;
}
