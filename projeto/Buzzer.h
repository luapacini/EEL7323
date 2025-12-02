#ifndef BUZZER_H
#define BUZZER_H    

#include <stdint.h>
#include "Atuador.h"

class Buzzer: public Atuador {
    private:
        int frequencia;
        volatile uint8_t *registrador; 
        uint8_t pino;
    public:
        Buzzer(int freq, volatile uint8_t *porta, uint8_t p);
        int getFrequencia();
        void setFrequencia(int newFreq);
        void ligar();
        void desligar();
};

#endif