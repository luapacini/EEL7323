#include "LED.h"

LED::LED(volatile uint8_t *porta, uint8_t p) {
    registrador = porta;
    pino = p;
}

int LED::getLuminosidade() {
    return luminosidade;
}
void LED::setLuminosidade(int newLumin) {
    luminosidade = newLumin;
}

void LED::ligar() {
    *registrador |= (1 << pino);
}

void LED::desligar() {
    *registrador &= ~(1<<pino);
}