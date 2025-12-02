#ifndef LED_H
#define LED_H    

#include <stdint.h>
#include "Atuador.h"

class LED: public Atuador {
    private:
        int luminosidade;
        volatile uint8_t *registrador; 
        uint8_t pino;
    public:
        LED(volatile uint8_t *porta, uint8_t p);
        int getLuminosidade();
        void setLuminosidade(int newLumin);
        void ligar();
        void desligar();
};

#endif