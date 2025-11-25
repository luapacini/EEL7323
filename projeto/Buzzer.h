#ifndef BUZZER_H
#define BUZZER_H    

#include "Atuador.h"

class Buzzer: public Atuador {
    private:
        int frequencia;
        bool estado;
    public:
        int getFrequencia();
        void setFrequencia(int newFreq);
        void ligar();
        void desligar();
        void toggle();
};

#endif