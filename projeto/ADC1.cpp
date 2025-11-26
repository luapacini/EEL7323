#include "ADC1.h"
#include "I2C.h"

uint16_t ADC1::moving_average(uint16_t new_sample)
{
    sum -= buffer[buffer_idx]; //remove a medida mais antiga da soma

    buffer[buffer_idx] = new_sample; // adiciona nova medida no buffer
    sum += new_sample; // adiciona nova medida na soma

    buffer_idx++; // incrementa o index

    if (buffer_idx >= ADC_BUFFER_SIZE) {
        buffer_idx = 0; // volta index para zero
    }

    return(sum / ADC_BUFFER_SIZE); // retorna media
}
// ---------------------------------------------------------------------------------------------------

// funcao de inicializacao
void ADC1::Init(uint8_t device_address, uint8_t channel, uint8_t gain, uint8_t mode, uint8_t data_rate, uint8_t comp_mode, uint8_t comp_pol, uint8_t comp_lat, uint8_t comp_que)
{
    uint8_t msg[3];

    msg[0] = CONFIG_REGIST; // endereco do Configuration Register 
    msg[1] = 0x00 | channel | gain | mode; // primeiro byte a ser setado no Configuration Register
    msg[2] = data_rate | comp_mode | comp_pol | comp_lat | comp_que; // segundo byte do Configuration Register

    I2C::WriteData(device_address, msg, 3); // escreve dados

    //escreve o endereco do Conversion Register para ser salvo no Address Pointr Register do ADS1115 para leituras futuras
    I2C::WriteData(device_address, CONV_REGIST, 1);

    if (gain == PGA_GAIN_FSR_6_144V) {
        conversion_constant = 6144;
    } else {
        conversion_constant = 4096;
    }
}
// ---------------------------------------------------------------------------------------------------

//funcao de leitura
uint32_t ADC1::Read(uint8_t device_address)
{
    uint8_t readings[2];

    I2C::ReadData(device_address, readings, 2); // pede 2 bytes do slave
    uint16_t value = (((uint16_t) readings[0]) << 8) | (readings[1] & 0x00FF);
    uint32_t voltage = (((uint32_t) value) * conversion_constant) >> 15; // [mV]

    return voltage;
}   