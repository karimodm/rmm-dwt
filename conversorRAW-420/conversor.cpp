//
// PRACTICAS REDES MULTIMEDIA (RMM)
// FACULTAD DE INFORMATICA - UPV
//
// COMPRESION DE IMAGEN - CONVERSION RGB a YCbCr
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ImagenES.h"
#include "RGBYCbCr.h"

#define RGBaYCbCr444 1
#define YCbCr444aRGB 2
#define RGBaYCbCr420 3
#define YCbCr420aRGB 4

#define RAW 1
#define YCbCr444 2
#define YCbCr420 3
#define NO_EXT 4
#define UNKNOWN 5

static char *ficheroRGBPorDefecto="lena.raw";
static char *fichero444PorDefecto="lena.444";
static char *fichero420PorDefecto="lena.420";
static int opcionPorDefecto=RGBaYCbCr444;
static int anchoPorDefecto=512;
static int altoPorDefecto=512;

static char *ficheroEntrada=ficheroRGBPorDefecto;
static char *ficheroSalida;
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
  else if (Mayusculas(Nombre[f])=='R' && Mayusculas(Nombre[f+1])=='A' && Mayusculas(Nombre[f+2])=='W')
	  return RAW;
  else if (Mayusculas(Nombre[f])=='4' && Mayusculas(Nombre[f+1])=='4' && Mayusculas(Nombre[f+2])=='4')
	  return YCbCr444;
  else if (Mayusculas(Nombre[f])=='4' && Mayusculas(Nombre[f+1])=='2' && Mayusculas(Nombre[f+2])=='0')
	  return YCbCr420;
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
		printf("Extensiones: \"raw\" para RGB, \".444\" para YCbCr 4:4:4 o \".420\" para YCbCr 4:2:0\n");
		exit(1); 
	}
	ancho=atoi(argv[5]);
	alto=atoi(argv[6]); 
	ficheroEntrada=argv[2];
	ficheroSalida=argv[4];
	if (DeterminaTipo(ficheroEntrada)==RAW && DeterminaTipo(ficheroSalida)==YCbCr444)
	  opcion=RGBaYCbCr444;
	else if (DeterminaTipo(ficheroEntrada)==RAW && DeterminaTipo(ficheroSalida)==YCbCr420)
	  opcion=RGBaYCbCr420;
	else if (DeterminaTipo(ficheroEntrada)==YCbCr444 && DeterminaTipo(ficheroSalida)==RAW)
	  opcion=YCbCr444aRGB;
	else if (DeterminaTipo(ficheroEntrada)==YCbCr420 && DeterminaTipo(ficheroSalida)==RAW)
	  opcion=YCbCr420aRGB;
	else
	{
		printf("\nConversion no implementada (comprueba las extensiones)\n"); 
		exit(1); 
	}
  }
}

int main(int argc, char **argv)
{
  unsigned char **R,**G,**B,**Y;
  signed char **Cr444, **Cb444, **Cb420, **Cr420;

  printf("\n--------------------------------\n");
  printf("PRACTICAS REDES MULTIMEDIA (RMM)\n");
  printf("Facultad de Informatica, UPV\n");
  printf("--------------------------------\n");
  printf("Practica de compresion de imagen\n");
  printf("1a parte - conversion RGB YCbCr\n");
  printf("--------------------------------\n");

  if (opcionPorDefecto==RGBaYCbCr444) ficheroSalida=fichero444PorDefecto;
    else ficheroSalida=fichero420PorDefecto;

  ProcesaArgumentos(argc,argv);

//  conversion RGB a YCbCr

  if (opcion==RGBaYCbCr444 || opcion==RGBaYCbCr420)
  {
    ReservaPlano(ancho, alto, &R);
    ReservaPlano(ancho, alto, &G);
    ReservaPlano(ancho, alto, &B);
    ReservaPlano(ancho, alto, &Y);
    ReservaPlano(ancho, alto, (unsigned char***)&Cb444);
    ReservaPlano(ancho, alto, (unsigned char***)&Cr444);
    if (CargaRawRGB(ficheroEntrada, ancho, alto, R,G,B)!=0)
	{
	  printf("Error al leer fichero\n");
	  exit(1);
	}    
    printf("\nConvirtiendo de RGB a YCbCr 4:4:4...\n");
	ConversionRGBaYCbCr444(ancho, alto, R, G, B, Y, Cb444, Cr444);
    LiberaPlano(ancho, alto, &R);
    LiberaPlano(ancho, alto, &G);
    LiberaPlano(ancho, alto, &B);	
	if (opcion==RGBaYCbCr444)
	{
	  if (GuardaRawYCbCr444(ficheroSalida, ancho, alto, Y, Cb444, Cr444)!=0)
	  {
			  printf("Error al escribir fichero\n");
	          exit(1);
	  }
	}
	else
	{  // Calcula la reduccion 420 si se ha pedido
      ReservaPlano(ancho/2, alto/2, (unsigned char***)&Cb420);
      ReservaPlano(ancho/2, alto/2, (unsigned char***)&Cr420);
      printf("\nConvirtiendo de YCbCr 4:4:4 a YCbCr 4:2:0...\n");
      ConversionYCbCr444aYCbCr420(ancho, alto, Cb444, Cr444, Cb420, Cr420);
	  if (GuardaRawYCbCr420(ficheroSalida, ancho, alto, Y, Cb420, Cr420)!=0)
	  {
			  printf("Error al escribir fichero\n");
	          exit(1);
	  }
      LiberaPlano(ancho/2, alto/2, (unsigned char***)&Cb420);
      LiberaPlano(ancho/2, alto/2, (unsigned char***)&Cr420);
	}
    LiberaPlano(ancho, alto, &Y);
    LiberaPlano(ancho, alto, (unsigned char***)&Cb444);
    LiberaPlano(ancho, alto, (unsigned char***)&Cr444);
  }

//  conversion YCbCr a RGB
  else
  {
    ReservaPlano(ancho, alto, &Y);
    ReservaPlano(ancho, alto, (unsigned char***)&Cb444);
    ReservaPlano(ancho, alto, (unsigned char***)&Cr444);
	if (opcion==YCbCr444aRGB)
	{
	  if (CargaRawYCbCr444(ficheroEntrada, ancho, alto, Y, Cb444, Cr444)!=0)
	  {
			  printf("Error al leer fichero\n");
	          exit(1);
	  }
	}
	else
	{  // Calcula la ampliacion de 420 
      ReservaPlano(ancho/2, alto/2, (unsigned char***)&Cb420);
      ReservaPlano(ancho/2, alto/2, (unsigned char***)&Cr420);
	  if (CargaRawYCbCr420(ficheroEntrada, ancho, alto, Y, Cb420, Cr420)!=0)
	  {
			  printf("Error al leer fichero\n");
	          exit(1);
	  }
      printf("\nConvirtiendo de YCbCr 4:2:0 a YCbCr 4:4:4...\n");
      ConversionYCbCr420aYCbCr444(ancho, alto, Cb420, Cr420, Cb444, Cr444);
      LiberaPlano(ancho/2, alto/2, (unsigned char***)&Cb420);
      LiberaPlano(ancho/2, alto/2, (unsigned char***)&Cr420);
	}
    ReservaPlano(ancho, alto, &R);
    ReservaPlano(ancho, alto, &G);
    ReservaPlano(ancho, alto, &B);
    printf("\nConvirtiendo de YCbCr 4:4:4 a RGB...\n");
	ConversionYCbCr444aRGB(ancho, alto, Y, Cb444, Cr444, R, G, B);
    if (GuardaRawRGB(ficheroSalida, ancho, alto, R,G,B)!=0)
	{
	  printf("Error al escribir fichero\n");
	  exit(1);
	}    
    LiberaPlano(ancho, alto, &R);
    LiberaPlano(ancho, alto, &G);
    LiberaPlano(ancho, alto, &B);	
    LiberaPlano(ancho, alto, &Y);
    LiberaPlano(ancho, alto, (unsigned char***)&Cb444);
    LiberaPlano(ancho, alto, (unsigned char***)&Cr444);
  }
  return 0;
}

