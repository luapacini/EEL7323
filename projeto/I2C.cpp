#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "ICP.h"
#include "Filters.h"

//using namespace tratadorICP;

namespace tratadorICP {
    volatile int32_t tempoAnterior = 0;
    volatile bool novaInterrupcao = false;
    volatile uint32_t diffTempo = 0;
    // volatile bool filterFlag = false;
    // volatile uint32_t previousValue = 0;

    oneEuroFilter oneEuro = oneEuroFilter();

    void ICPConfig(){ //configura ICP3
        //------- Input Capture
        TIMSK3 |= (1 << ICIE3) | (1<<TOIE3); //interrupcao de captura e overflow habilitados
        TCCR3B = (1 << ICNC3) | (1 << ICES3) | (1 << CS30); //ativa Input Capture Noise Canceler, configura ICP3 para rising edge, no prescaling
        TCNT3 = 0; // zera contador
    }

    uint32_t retornaDiff() {
        return diffTempo;
    }

    bool confereFlag() {
        bool aux;
        aux = novaInterrupcao;
        novaInterrupcao = false;
        return aux;
    }

    ISR(TIMER3_CAPT_vect) {
        cli();

        uint16_t tempoAtual = ICR3;

        tempoAtual = oneEuro.filtering(tempoAtual);

        diffTempo = (((int32_t)tempoAtual) - tempoAnterior)>>4;
        // if (diffTempo > 10) {
            tempoAnterior = tempoAtual;
            novaInterrupcao = true;
        // }
        sei();
    }

    ISR(TIMER3_OVF_vect) {
        tempoAnterior -= 0x10000;
    }
}
