#include "LDR.h"


LDR::LDR(volatile uint8_t* portaLed, uint8_t pinoLed) 
    : LED1(portaLed, pinoLed)
{    
    luminosidade = 50;
}

//retorna luminosidade em % utilizando log para resposta mais realista
void LDR::calcularLuminosidade() {
    if(ADS1115.Read(ADS1115_ADDRESS_SDA) <= 0.0f) {
        luminosidade = 0;
    } else {
        luminosidade = 100.0f / (1 + LDR::ln_approx(ADS1115.Read(ADS1115_ADDRESS_SDA) / 1000.0f));
    }
    adicionaBuffer1(luminosidade);
}

void LDR::ajustarLED(bool &flagLuminosidade) {
    LED1.ligar();
    if(luminosidade<60) {
        LED1.setLuminosidade(60-luminosidade);
    } else {
        flagLuminosidade = true;
    }
}

float LDR::ln_approx(float x) { //AVR nao comporta cmath, essa funcao aproxima log
    if (x <= 0.0f) return 0.0f; // evita log de zero ou negativo

    float y = (x - 1.0f) / (x + 1.0f);
    float y2 = y * y;
    return 2.0f * (y + y2*y/3.0f + y2*y2*y/5.0f);
}

void LDR::iniciaADC(uint8_t device_address, uint8_t channel, uint8_t gain, uint8_t mode, uint8_t data_rate, uint8_t comp_mode, uint8_t comp_pol, uint8_t comp_lat, uint8_t comp_que) {
    ADS1115.Init(device_address, channel, gain, mode, data_rate, comp_mode, comp_pol, comp_lat, comp_que);
}
