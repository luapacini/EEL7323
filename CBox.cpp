#ifndef CBOX
#define CBOX

#include <iostream>
#include "CShape3d.cpp"

class box: public shape3D {
    public:
        box(float alt, float larg, float comp);        
        float calculaVolume();
};

box::box(float alt, float larg, float comp) {
    setAltura(alt);
    setLargura(larg);
    setComprimento(comp);
}

float box::calculaVolume() {
    return getAltura()*getLargura()*getComprimento();
}

#endif