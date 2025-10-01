#include <iostream>
#include <math.h>
#include "CShape3d.cpp"

class cilindro: shape3D {
    public:
        cilindro(float alt, float r);
        float calculaVolume(float alt, float r);
};

cilindro::cilindro(float alt, float r) {
    altura = alt;
    raio = r;
}

float cilindro::calculaVolume(float alt, float r) {
    return M_PI*r*r*alt;
}