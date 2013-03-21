#include "Pixel.h"
//test
Pixel::Pixel() {}

Pixel::Pixel(float Y, float Cb, float Cr) {
	this->Y  = Y;
	this->Cb = Cb;
	this->Cr = Cr;
}

Pixel::Pixel(Pixel &r) {
	Y  = r.Y;
	Cb = r.Cb;
	Cr = r.Cr;
}

Pixel &Pixel::operator+(Pixel &der) {
	Y  += der.Y;
	Cb += der.Cb;
	Cr += der.Cr;
	return *this;
}

Pixel &Pixel::operator*(Pixel &der) {
	Y  *= der.Y;
	Cb *= der.Cb;
	Cr *= der.Cr;
	return *this;
}

Pixel &Pixel::set(float Y, float Cb, float Cr) {
	this->Y  = Y;
	this->Cb = Cb;
	this->Cr = Cr;
	return *this;
}

Pixel::Pixel &operator=(Pixel &r) {
  if (r == *this) return *this;
  Y  = r.Y;
	Cb = r.Cb;
	Cr = r.Cr;
	return *this;
}

void Pixel::value(float *Y, float *Cb, float *Cr) {
	*Y  = this->Y;
	*Cb = this->Cb;
	*Cr = this->Cr;
}

