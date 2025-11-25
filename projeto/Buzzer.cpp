#include "Buzzer.h"

int Buzzer::getFrequencia() {
    return frequencia;
}

void Buzzer::setFrequencia(int newFreq) {
    frequencia = newFreq;
}

void Buzzer::ligar(bool estado) {
    estado = true;
}

void Buzzer::desligar(bool estado) {
    estado = false;
}

void Buzzer::toggle(bool estado) {
    estado = !estado;
}