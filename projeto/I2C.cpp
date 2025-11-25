#include "I2C.h"
#include "Serial.h"
---------------------------------------------------------------------------------------------------

//seta os pinos de interrupcao e habilita comunicacao TWI 
void I2C::Init(uint16_t speed)
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
bool I2C::TimeOut(void) 
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
void I2C::SendStart(void) 
{
    TWCR0 = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN); 
    I2C::TimeOut();
}
// ---------------------------------------------------------------------------------------------------

//manda uma condicao de parada
void I2C::SendStop(void) 
{
    TWCR0 = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
    uint8_t TOut = 100;
    while ((TWCR & (1<<TWSTO)) && TOut > 0) { TOut--; _delay_us(10); }

}

// ---------------------------------------------------------------------------------------------------

//carrega o byte no registrador TWDR
void I2C::WriteDataByte(uint8_t data) 
{
    TWDR0 = data; //seta o registrador TWDR com o dado a ser transmitido
    TWCR0 = (1 << TWINT) | (1 << TWEN); 

    if (I2C_::TimeOut()) {
        return;
    }
}

// ---------------------------------------------------------------------------------------------------

void I2C::StartTransmission(uint8_t slave_address) 
{
    I2C::SendStart();
    I2C::WriteDataByte(slave_address << 1);
}

// ---------------------------------------------------------------------------------------------------

void I2C::RequestTransmission(uint8_t slave_address) 
{
    I2C::SendStart(); // envia a condicao de inicio

    TWDR0 = (slave_address << 1) | 0x01; //seta o registrador TWDR com o endereco do dispositivo e um bit de leitura
    TWCR0 = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);

    if (I2C::TimeOut()) {
        return;
    }
}

// ---------------------------------------------------------------------------------------------------

//le um byte de dado no registrador TWDR
uint16_t I2C::ReadDataByte(bool ack) 
{
    TWCR0 = (1 << TWINT) | (1 << TWEN) | (ack ? 1 << TWEA : 0);

    if (I2C::TimeOut()) {
        return 0x8000;
    }

    return TWDR0;
}

// ---------------------------------------------------------------------------------------------------

//escreve um numero especificado de bytes de dado no registrador TWDR
void I2C::WriteData(uint8_t device_address, uint8_t *data, uint8_t length)
{
    I2C::StartTransmission(device_address);

    for (int i = 0; i < length; i++) {
        I2C::WriteDataByte(data[i]);
    }

    I2C::SendStop();
}

// ---------------------------------------------------------------------------------------------------

//le um numero especificado de bytes de dado no registrador TWDR
void I2C::ReadData(uint8_t device_address, uint8_t *data, uint8_t bytes_num)
{
    uint8_t index = 0;

    I2C::RequestTransmission(device_address);

    while (bytes_num > 0) {
        bytes_num--;
        uint16_t byte_read = I2C::ReadDataByte((bytes_num > 0) ? true : false);
        if(byte_read == 0x8000){
            Serial::println("erro recebendo dados");
            I2C::SendStop();
            return;
        }
        data[index++] = byte_read;
    }
    
    I2C::SendStop();
}