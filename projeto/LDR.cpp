#include "LDR.h"

//retorna luminosidade em % utilizando log para resposta mais realista
void LDR::calcularLuminosidade() {
    if(ADS1115.Read(ADS1115_ADDRESS_SDA) <= 0.0f) {
        luminosidade = 0;
    } else {
        luminosidade = 100.0f / (1 + LDR::ln_approx(ADS1115.Read(ADS1115_ADDRESS_SDA) / 1000.0f));
    }
    adicionaBuffer1(luminosidade);
}

void LDR::ajustarLED(LED , bool &flagLuminosidade) {
    if(luminosidade<60) {
        LED1.setLuminosidade(60-luminosidade);
    } else {
        flagLuminosidade = true;
    }
}

float LDR::ln_approx(float x) {
    if (x <= 0.0f) return 0.0f; // evita log de zero ou negativo

    float y = (x - 1.0f) / (x + 1.0f);
    float y2 = y * y;
    // Aproximação com 3 termos da série de Taylor
    return 2.0f * (y + y2*y/3.0f + y2*y2*y/5.0f);
}