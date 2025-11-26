#include <cmath>
#include "LDR.h"

//retorna luminosidade em % utilizando log para resposta mais realista
void LDR::calcularLuminosidade() {
        luminosidade = 100.0f / (1 + log(ADS1115.Read(ADS1115_ADDRESS_SDA) / 1000.0f));
}

void LDR::ajustarLED(LED LEDacionado) {
    if(luminosidade<60) {
        LEDacionado.setLuminosidade(60-luminosidade);
        adicionaBuffer1(luminosidade);
    } else {
        //ativar excecao. como?
    }
}