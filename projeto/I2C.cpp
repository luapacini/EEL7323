#include "I2C.h"
#include "Serial.h"

#include <avr/io.h>
#include <util/delay.h>

#ifndef TWSR0
    #undef TWBR0
    #define TWBR0 TWBR
    #define TWSR0 TWSR
    #define TWAR0 TWAR
    #define TWDR0 TWDR
    #define TWCR0 TWCR
    #define TWAMR0 TWAMR
#endif


#define BIT_SET(REG, BIT)        REG |=  (1<<BIT)
#define BIT_CLEAR(REG, BIT)      REG &= ~(1<<BIT)

#define BIT_CHECK(REG, BIT)      ((REG >> BIT) & 1)

// ---------------------------------------------------------------------------------------------------

//seta os pinos de interrupcao e habilita comunicacao TWI 
void I2C_Init(uint16_t speed)
{
    TWSR0 = 0; //seta prescaler bits em 0

    if (speed == 400) {
        TWBR0 = 12;
    } else {
        TWBR0 = 72;
    }
}

// ---------------------------------------------------------------------------------------------------

//configura um timeout para a espera da flag TWINT ser setada
bool I2C_TimeOut(void) 
{
    uint8_t delay = 200;

    while ((BIT_CHECK(TWCR0, TWINT) == 0) && (delay > 0)) {
        delay--;
        _delay_us(10);
    }

    if (delay == 0) {
        Serial::println("Timeout.");
        return true;
    }
    
    return false;
}

// ---------------------------------------------------------------------------------------------------

//manda uma condicao de inicio
void I2C_SendStart(void) 
{
    TWCR0 = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN); 
    I2C_TimeOut();
}
// ---------------------------------------------------------------------------------------------------

//manda uma condicao de parada
void I2C_SendStop(void) 
{
    TWCR0 = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
    uint8_t TOut = 100;
    while ((TWCR & (1<<TWSTO)) && TOut > 0) { TOut--; _delay_us(10); }

}

// ---------------------------------------------------------------------------------------------------

//carrega o byte no registrador TWDR
void I2C_WriteDataByte(uint8_t data) 
{
    TWDR0 = data; //seta o registrador TWDR com o dado a ser transmitido
    TWCR0 = (1 << TWINT) | (1 << TWEN); 

    if (I2C_TimeOut()) {
        return;
    }
}

// ---------------------------------------------------------------------------------------------------

void I2C_StartTransmission(uint8_t slave_address) 
{
    I2C_SendStart();
    I2C_WriteDataByte(slave_address << 1);
}

// ---------------------------------------------------------------------------------------------------

void I2C_RequestTransmission(uint8_t slave_address) 
{
    I2C_SendStart(); // envia a condicao de inicio

    TWDR0 = (slave_address << 1) | 0x01; //seta o registrador TWDR com o endereco do dispositivo e um bit de leitura
    TWCR0 = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);

    if (I2C_TimeOut()) {
        return;
    }
}

// ---------------------------------------------------------------------------------------------------

//le um byte de dado no registrador TWDR
uint16_t I2C_ReadDataByte(bool ack) 
{
    TWCR0 = (1 << TWINT) | (1 << TWEN) | (ack ? 1 << TWEA : 0);

    if (I2C_TimeOut()) {
        return 0x8000;
    }

    return TWDR0;
}

// ---------------------------------------------------------------------------------------------------

//escreve um numero especificado de bytes de dado no registrador TWDR
void I2C_WriteData(uint8_t device_address, uint8_t *data, uint8_t length)
{
    I2C_StartTransmission(device_address);

    for (int i = 0; i < length; i++) {
        I2C_WriteDataByte(data[i]);
    }

    I2C_SendStop();
}

// ---------------------------------------------------------------------------------------------------

//le um numero especificado de bytes de dado no registrador TWDR
void I2C_ReadData(uint8_t device_address, uint8_t *data, uint8_t bytes_num)
{
    uint8_t index = 0;

    I2C_RequestTransmission(device_address);

    while (bytes_num > 0) {
        bytes_num--;
        uint16_t byte_read = I2C_ReadDataByte((bytes_num > 0) ? true : false);
        if(byte_read == 0x8000){
            Serial::println("erro recebendo dados");
            I2C_SendStop();
            return;
        }
        data[index++] = byte_read;
    }
    
    I2C_SendStop();
}