#ifndef CSHAPE3D
#define CSHAPE3D

#include <iostream>

class shape3D {
    private:
        float altura;
        float largura;
        float comprimento;
        float raio;
    public:
        void setAltura(float newAltura);
        void setLargura(float newLargura);
        void setComprimento(float newComprimento);
        void setRaio(float newRaio);
        float getAltura();
        float getLargura();
        float getComprimento();
        float getRaio();

        float calculaVolume() { return 0.0; };
};

void shape3D::setAltura(float newAltura) {
    altura = newAltura;
}

void shape3D::setRaio(float newRaio) {
    raio = newRaio;
}

void shape3D::setLargura(float newLargura) {
    largura = newLargura;
}

void shape3D::setComprimento(float newComprimento) {
    comprimento = newComprimento;
}

float shape3D::getAltura() {
    return altura;
}

float shape3D::getRaio() {
    return raio;
}

float shape3D::getLargura() {
    return largura;
}

float shape3D::getComprimento() {
    return comprimento;
}

#endif