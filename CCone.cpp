#ifndef CCONE
#define CCONE

#include <iostream>
#include <math.h>
#include "CShape3d.cpp"

class cone: public shape3D {
    public:
        cone(float r, float alt);
        float calculaVolume();
};

cone::cone(float r, float alt) {
    setAltura(alt);
    setRaio(r);
}

float cone::calculaVolume() {
    return 3.14159*getRaio()*getRaio()*getAltura()/3;
}

#endif