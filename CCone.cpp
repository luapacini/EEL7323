#include <iostream>
#include <math.h>
#include "CShape3d.cpp"

class cone: shape3D {
    public:
        cone(float alt, float r);
        float calculaVolume(float alt, float r);
};

cone::cone(float alt, float r) {
    setAltura(alt);
    setRaio(r);
}

float cone::calculaVolume(float alt, float r) {
    return M_PI*r*r*alt/3;
}