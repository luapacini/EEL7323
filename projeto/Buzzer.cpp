#include "Buzzer.h"

Buzzer::Buzzer(int freq, bool est) {
    frequencia = freq;
    estado = est;
}

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
