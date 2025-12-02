#include "Buzzer.h"

Buzzer::Buzzer(int freq, volatile uint8_t *porta, uint8_t p) {
    frequencia = freq;
    registrador = porta;
    pino = p;
    Buzzer::desligar();
}

int Buzzer::getFrequencia() {
    return frequencia;
}

void Buzzer::setFrequencia(int newFreq) {
    frequencia = newFreq;
}

void Buzzer::ligar() {
    *registrador |= (1 << pino);
}

void Buzzer::desligar() {
    *registrador &= ~(1<<pino);
}
