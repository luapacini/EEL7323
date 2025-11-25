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
    while (lengthOfMsg-- > 0) init = CRC_lookup[ (init ^ *msg++)];
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

    I2C::WriteData(SHT30_ADDRESS, msg, 2); // Writes the data

    _delay_ms(3000);
}

uint8_t SHT30::periodicAquisition() {
    uint8_t msg[2];

    msg[0] = 0xE0; //tabela 11 datasheet /fetch data/
    msg[1] = 0x00; //tabela 11 datasheet /fetch data/

    I2C::WriteData(SHT30_ADDRESS, msg, 2); //escreve
    
    I2C::ReadData(SHT30_ADDRESS, leitura, 6);

    if (breakFlag == 2) return 0; //nao imprimir duas vezes "Break conluido"

    if (breakFlag == 1) {
        Serial::println("Break concluido");
        breakFlag++;
        return 0;
    }

    uint16_t rawTemperature = (uint16_t)((((uint16_t)leitura[0]) << 8) | leitura[1]); // 8MSB da temperatura deslocados pra esquerda e ou logico com 8LSB
    uint8_t tempCRC = leitura[2];
    uint16_t rawHumidity = (uint16_t)((((uint16_t)leitura[3]) << 8) | leitura[4]); //mesma coisa umidade
    uint8_t humCRC = leitura[5];

    if (SHT30::crc8(&(leitura[0]), 2, initCRC) == tempCRC && SHT30::crc8(&(leitura[3]), 2, initCRC) == humCRC) {
        // Calculate temperature and humidity  
        temp = -45000 + 175000 * (rawTemperature / 65535.0); 
        umidade = 100 * (rawHumidity / 65535.0);

        char buffer[10];
        snprintf(buffer, 10, "%u", (unsigned int)(temp));
        Serial::print("Temperatura = "); Serial::print(buffer); Serial::println(" mºC");
        snprintf(buffer, 10, "%u", (unsigned int) umidade);
        Serial::print("Umidade = "); Serial::print(buffer); Serial::println("%"); Serial::println("");
        _delay_ms(2000);
    } else {
        Serial::println("Houve problema no CRC, nao eh possivel printar resultado");
    }
    return 0;
}

uint8_t SHT30::periodicAquisitionBreak() {
    uint8_t msg[2];

    msg[0] = 0x30; 
    msg[1] = 0x93; 

    I2C::WriteData(SHT30_ADDRESS, msg, 2); // escreve dados

    Serial::println("--- Break ---"); Serial::println(" ");
    return 1;
}

void SHT30::oneShotAquisition() {
    I2C::ReadData(SHT30_ADDRESS, leitura, 6);

    uint16_t rawTemperature = (uint16_t)((((uint16_t)leitura[0]) << 8) | leitura[1]); // 8MSB da temperatura deslocados pra esquerda e ou logico com 8LSB
    uint8_t tempCRC = leitura[2];
    uint16_t rawHumidity = (uint16_t)((((uint16_t)leitura[3]) << 8) | leitura[4]); //mesma coisa umidade
    uint8_t humCRC = leitura[5];

    if (SHT30::crc8(&(leitura[0]), 2, initCRC) == tempCRC && SHT30::crc8(&(leitura[3]), 2, initCRC) == humCRC) {
        // Calculate temperature and humidity  
        temp = -45000 + 175000 * (rawTemperature / 65535.0); 
        umidade = 100 * (rawHumidity / 65535.0);

        char buffer[10];
        snprintf(buffer, 10, "%u", (unsigned int)(temp));
        Serial::print("Temperatura = "); Serial::print(buffer); Serial::println(" mºC");
        snprintf(buffer, 10, "%u", (unsigned int) umidade);

        Serial::print("Umidade = "); Serial::print(buffer); Serial::println("%"); Serial::println("");
        _delay_ms(2000);
    } else {
        Serial::println("Houve problema no CRC, nao eh possivel printar resultado");
    }
}
