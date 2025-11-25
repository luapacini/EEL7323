#include "Buzzer.h"

int Buzzer::getFrequencia() {
    return frequencia;
}

void Buzzer::setFrequencia(int newFreq) {
    frequencia = newFreq;
}

void Buzzer::ligar() {
    estado = true;
}

void Buzzer::desligar() {
    estado = false;
}

void Buzzer::toggle() {
    estado = !estado;
}