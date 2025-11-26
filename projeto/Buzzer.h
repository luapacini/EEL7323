#ifndef BUZZER_H
#define BUZZER_H    

#include "Atuador.h"

class Buzzer: public Atuador {
    private:
        int frequencia;
        bool estado;
    public:
        Buzzer(int freq, bool est);
        int getFrequencia();
        void setFrequencia(int newFreq);
        void ligar();
        void desligar();
};

#endif