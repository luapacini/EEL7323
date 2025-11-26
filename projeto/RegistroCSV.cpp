#include "RegistroCSV.h"

// Endereços EEPROM
uint8_t EEMEM eepromCabecalho;
RegistroCSV::POD EEMEM eepromRegistros[MAX_REGISTROS];
uint16_t EEMEM eepromIndice;

// ======================================
// Implementação da classe RegistroCSV
// ======================================

RegistroCSV::RegistroCSV() : temperatura(0), umidade(0), luminosidade(0) {}

void RegistroCSV::setTemp(float t) { temperatura = t; }
void RegistroCSV::setUmid(float u) { umidade = u; }
void RegistroCSV::setLumin(float l) { luminosidade = l; }

float RegistroCSV::getTemp() const { return temperatura; }
float RegistroCSV::getUmid() const { return umidade; }
float RegistroCSV::getLumin() const { return luminosidade; }

RegistroCSV::POD RegistroCSV::toPOD() const {
    POD pod;
    pod.temperatura  = temperatura;
    pod.umidade      = umidade;
    pod.luminosidade = luminosidade;
    return pod;
}

void RegistroCSV::fromPOD(const POD& pod) {
    temperatura  = pod.temperatura;
    umidade      = pod.umidade;
    luminosidade = pod.luminosidade;
}

// ======================================
// Funções EEPROM
// ======================================

void initEEPROM_CSV() {
    uint8_t flag = eeprom_read_byte(&eepromCabecalho);
    if (flag != 0xA5) {
        uint16_t zero = 0;
        eeprom_update_word(&eepromIndice, zero);
        eeprom_update_byte(&eepromCabecalho, 0xA5);
    }
}

void salvarCSVexcecao(SHT30 &sht, LDR &ldr) {
    initEEPROM_CSV();

    uint16_t index = eeprom_read_word(&eepromIndice);
    if (index >= MAX_REGISTROS) index = 0;

    RegistroCSV reg;
    reg.setTemp(sht.getLastData1());
    reg.setUmid(sht.getLastData2());
    reg.setLumin(ldr.getLastData1());

    RegistroCSV::POD pod = reg.toPOD();
    eeprom_update_block(&pod, &eepromRegistros[index], sizeof(RegistroCSV::POD));

    index++;
    eeprom_update_word(&eepromIndice, index);
}
