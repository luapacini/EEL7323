#include <cmath>
#include "LDR.h"
#include "SensorException.h"

//retorna luminosidade em % utilizando log para resposta mais realista
void LDR::calcularLuminosidade() {
    if(ADS1115.Read(ADS1115_ADDRESS_SDA) <= 0.0f) {
        luminosidade = 0;
    } else {
        luminosidade = 100.0f / (1 + log(ADS1115.Read(ADS1115_ADDRESS_SDA) / 1000.0f));
    }
    adicionaBuffer1(luminosidade);
}

void LDR::ajustarLED(LED LEDacionado) {
    if(luminosidade<60) {
        LEDacionado.setLuminosidade(60-luminosidade);
    } else {
        throw LuminosidadeException(luminosidade);
    }
}