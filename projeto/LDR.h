#ifndef LDR_H
#define LDR_H

#include "ADC1.h"
#include "LED.h"
#include "Sensor.h"

class LDR: public Sensor {
    private:
        ADC1 ADS1115;
        LED LED1;
        float luminosidade = 50;
        float ln_approx(float x);
    public:
        LDR(volatile uint8_t* portaLed, uint8_t pinoLed);
        void calcularLuminosidade();
        void ajustarLED(bool &flagLuminosidade);
        void iniciaADC(uint8_t device_address, uint8_t channel, uint8_t gain, uint8_t mode, uint8_t data_rate, uint8_t comp_mode, uint8_t comp_pol, uint8_t comp_lat, uint8_t comp_que);
};

#endif