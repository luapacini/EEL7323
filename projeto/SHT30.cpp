#include <util/delay.h>
#include <stdio.h>

#include "SHT30.h"
#include "Serial.h"
#include "I2C.h"
    
bool SHT30::getModoAquisicao(){
    return modoAquisicao;
}
void SHT30::setModoAquisicao(bool modo){
    modoAquisicao = modo;
}

uint8_t SHT30::crc8(uint8_t *msg, int lengthOfMsg, uint8_t init) {
    while (lengthOfMsg-- > 0) init = CRC_lookup[(init ^ *msg++)];
    return init;
}

void SHT30::aquisitionSetup() {
    uint8_t msg[2];
    
    if(modoAquisicao) {
        msg[0] = 0x21; //tabela 10 datasheet, 1mps, MSB
        msg[1] = 0x30;//tabela 10 datasheet, high repeatability, LSB
        Serial::println("--- Periodic Aquisition Mode ---"); Serial::println(" ");
    } else {
        msg[0] = 0x2C; //tabela 9 datasheet, MSB
        msg[1] = 0x06; //tabela 9 datasheet, LSB
        Serial::println("--- One Shot Aquisition Mode ---"); Serial::println("");
    }

    I2C::WriteData(SHT30_ADDRESS, msg, 2);

    _delay_ms(3000);
}

void SHT30::periodicAquisition() {
    uint8_t msg[2];

    msg[0] = 0xE0; //tabela 11 datasheet /fetch data/
    msg[1] = 0x00; //tabela 11 datasheet /fetch data/

    I2C::WriteData(SHT30_ADDRESS, msg, 2); //escreve
    
    I2C::ReadData(SHT30_ADDRESS, leitura, 6);

    uint16_t rawTemperature = (uint16_t)((((uint16_t)leitura[0]) << 8) | leitura[1]); // 8MSB da temperatura deslocados pra esquerda e ou logico com 8LSB
    uint8_t tempCRC = leitura[2];
    uint16_t rawHumidity = (uint16_t)((((uint16_t)leitura[3]) << 8) | leitura[4]); //mesma coisa umidade
    uint8_t humCRC = leitura[5];

    if (SHT30::crc8(&(leitura[0]), 2, initCRC) == tempCRC && SHT30::crc8(&(leitura[3]), 2, initCRC) == humCRC) {
        // calcula temperatura e umidade
        temp    = -45.0f + 175.0f * (rawTemperature / 65535.0f);
        umidade = 100.0f * (rawHumidity / 65535.0f);
        
        adicionaBuffer1(temp);     //guarda temperatura
        adicionaBuffer2(umidade);  // guarda umidade
    } else {
        Serial::println("Houve problema no CRC, nao eh possivel printar resultado");
    }
}

void SHT30::oneShotAquisition() {
    I2C::ReadData(SHT30_ADDRESS, leitura, 6);

    uint16_t rawTemperature = (uint16_t)((((uint16_t)leitura[0]) << 8) | leitura[1]); // 8MSB da temperatura deslocados pra esquerda e ou logico com 8LSB
    uint8_t tempCRC = leitura[2];
    uint16_t rawHumidity = (uint16_t)((((uint16_t)leitura[3]) << 8) | leitura[4]); //mesma coisa umidade
    uint8_t humCRC = leitura[5];

    if (SHT30::crc8(&(leitura[0]), 2, initCRC) == tempCRC && SHT30::crc8(&(leitura[3]), 2, initCRC) == humCRC) {
        // calcula temperatura e umidade 
        temp    = -45.0f + 175.0f * (rawTemperature / 65535.0f);
        umidade = 100.0f * (rawHumidity / 65535.0f);

        adicionaBuffer1(temp);     //guarda temperatura
        adicionaBuffer2(umidade);  // guarda umidade

        _delay_ms(2000);
    } else {
        Serial::println("Houve problema no CRC, nao eh possivel printar resultado");
    }
}
