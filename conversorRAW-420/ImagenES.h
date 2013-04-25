#ifndef ImagenESH
#define ImagenESH

//  RUTINAS PARA RESERVA DE MEMORIA

void ReservaPlano(int ancho, int alto, unsigned char ***Plano);
void LiberaPlano(int ancho, int alto, unsigned char ***Plano);

// RUTINAS PARA EL MANEJO DE FICHEROS DE LUMINANCIAS (Y)

int CargaRawLuminancia(char *Nombre, int ancho, int alto, unsigned char **Buffer);
int GuardaRawLuminancia(char *Nombre, int ancho, int alto, unsigned char **Buffer);

// RUTINAS PARA EL MANEJO DE FICHEROS RGB

int CargaRawRGB(char *Nombre, int ancho, int alto, unsigned char **R, unsigned char **G, unsigned char **B);
int GuardaRawRGB(char *Nombre, int ancho, int alto, unsigned char **R, unsigned char **G, unsigned char **B);

// RUTINAS PARA EL MANEJO DE FICHEROS YCbCr

int CargaRawYCbCr420(char *Nombre, int ancho, int alto, unsigned char **Y, signed char **Cb, signed char **Cr);
int CargaRawYCbCr444(char *Nombre, int ancho, int alto, unsigned char **Y, signed char **Cb, signed char **Cr);
int GuardaRawYCbCr420(char *Nombre, int ancho, int alto, unsigned char **Y, signed char **Cb, signed char **Cr);
int GuardaRawYCbCr444(char *Nombre, int ancho, int alto, unsigned char **Y, signed char **Cb, signed char **Cr);

#endif
