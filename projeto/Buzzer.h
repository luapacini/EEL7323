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
        void ligar(bool estado);
        void desligar(bool estado);
        void toggle(bool estado);
};

#endif