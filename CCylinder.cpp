#include <iostream>
#include <math.h>
#include "CShape3d.cpp"

class cilindro: public shape3D {
    public:
        cilindro(float alt, float r);
        float calculaVolume(float alt, float r);
};

cilindro::cilindro(float alt, float r) {
    setAltura(alt);
    setRaio(r);
}

float cilindro::calculaVolume(float alt, float r) {
    return 3.14159*r*r*alt;
}