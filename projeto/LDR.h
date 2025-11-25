#ifndef LDR_H
#define LDR_H

#include "ADC.h"
#include "LED.h"
#include "Sensor.h"

class LDR: public Sensor {
    private:
        ADC ADS1115;
        LED LED1;
        float luminosidade;
    public:
        void calcularLuminosidade();
        void ajustarLED(LED LEDacionado);
};

#endif