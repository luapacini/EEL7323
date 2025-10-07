#ifndef CCYLINDER
#define CCYLINDER

#include <iostream>
#include <math.h>
#include "CShape3d.cpp"

class cilindro: public shape3D {
    public:
        cilindro(float r, float alt);
        float calculaVolume();
};

cilindro::cilindro(float r, float alt) {
    setAltura(alt);
    setRaio(r);
}

float cilindro::calculaVolume() {
    return 3.14159*getRaio()*getRaio()*getAltura();
}

#endif