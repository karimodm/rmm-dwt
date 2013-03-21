#ifndef PIXEL_H
#define PIXEL_H

class Pixel {
	public:
		float Y;
		float Cb;
		float Cr;
		Pixel();
		Pixel(float, float, float);
		Pixel(Pixel&);
		Pixel &operator+(Pixel&);
		Pixel &operator*(float);
  	Pixel &operator=(Pixel&);
  	Pixel &set(float, float, float)
		void value(float *, float *, float *);
};

#endif
