#ifndef LDR_H
#define LDR_H

#include "ADC1.h"
#include "LED.h"
#include "Sensor.h"

class LDR: public Sensor {
    private:
        ADC1 ADS1115;
        LED LED1;
        float luminosidade;
        float ln_approx(float x);
    public:
        void calcularLuminosidade();
        void ajustarLED(LED LEDacionado, bool &flagLuminosidade);
};

#endif