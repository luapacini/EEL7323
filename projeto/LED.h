#ifndef LED_H
#define LED_H    

#include "Atuador.h"

class LED: public Atuador {
    private:
        int luminosidade;
    public:
        int getLuminosidade();
        void setLuminosidade(int newLumin);
};

#endif