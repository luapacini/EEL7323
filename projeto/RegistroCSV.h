#ifndef REGISTROCSV_H
#define REGISTROCSV_H

#include <avr/eeprom.h>
#include <stdint.h>
#include "LDR.h"
#include "SHT30.h"

#define MAX_REGISTROS 50

class RegistroCSV {
    private:
        float temperatura;
        float umidade;
        float luminosidade;

    public:
        RegistroCSV();
        struct POD {
            float temperatura;
            float umidade;
            float luminosidade;
        };

        void setTemp(float t);
        void setUmid(float u);
        void setLumin(float l);

        float getTemp() const;
        float getUmid() const;
        float getLumin() const;

        POD toPOD() const;
        void fromPOD(const POD& pod);
    };

// Funções para salvar/ler EEPROM
void initEEPROM_CSV();
void salvarCSVexcecao(class SHT30 &sht, class LDR &ldr);

#endif
