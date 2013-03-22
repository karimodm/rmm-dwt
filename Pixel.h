#ifndef PIXEL_H
#define PIXEL_H

class Pixel {
  public:
    float Y;
    float Cb;
    float Cr;
    Pixel();
    Pixel(float, float, float);
    Pixel operator+(const Pixel&);
    Pixel &operator+=(const Pixel&);
    Pixel operator*(float);
    Pixel &operator*=(float);
    Pixel &operator=(const Pixel&);
    Pixel &set(float, float, float);
    void value(float *, float *, float *);
};

#endif
