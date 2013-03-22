#include "Pixel.h"

Pixel::Pixel() {}

Pixel::Pixel(float Y, float Cb, float Cr) : Y(Y), Cb(Cb), Cr(Cr) { }

Pixel Pixel::operator+(const Pixel &der) {
  return Pixel(Y + der.Y, Cb + der.Cb, Cr + der.Cr);
}

Pixel &Pixel::operator+=(const Pixel &der) {
  Y  += der.Y;
  Cb += der.Cb;
  Cr += der.Cr;
  return *this;
}

Pixel Pixel::operator*(float k) {
  return Pixel(Y * k, Cb * k, Cr * k);
}

Pixel &Pixel::operator*=(float k) {
  Y  *= k;
  Cb *= k;
  Cr *= k;
  return *this;
}

Pixel &Pixel::operator=(const Pixel &r) {
  if (&r == this) return *this;
  Y  = r.Y;
  Cb = r.Cb;
  Cr = r.Cr;
  return *this;
}
  
Pixel &Pixel::set(float Y, float Cb, float Cr) {
  this->Y  = Y;
  this->Cb = Cb;
  this->Cr = Cr;
  return *this;
}

void Pixel::value(float *Y, float *Cb, float *Cr) {
  *Y  = this->Y;
  *Cb = this->Cb;
  *Cr = this->Cr;
}

