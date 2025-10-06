#include <iostream>
#include "CShape3d.cpp"

class box: public shape3D {
    public:
        box(float alt, float larg, float comp);        
        float calculaVolume(float alt, float larg, float comp);
};

box::box(float alt, float larg, float comp) {
    setAltura(alt);
    setLargura(larg);
    setComprimento(comp);
}

float box::calculaVolume(float alt, float larg, float comp) {
    return alt*larg*comp;
}