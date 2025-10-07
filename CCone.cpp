#ifndef CCONE
#define CCONE

#include <iostream>
#include <math.h>
#include "CShape3d.cpp"

class cone: public shape3D {
    public:
        cone(float alt, float r);
        float calculaVolume();
};

cone::cone(float alt, float r) {
    setAltura(alt);
    setRaio(r);
}

float cone::calculaVolume() {
    return 3.14159*getRaio()*getRaio()*getAltura()/3;
}

#endif