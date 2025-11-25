#ifndef I2C_H
#define I2C_H

#include <stdint.h>

void I2C_Init(uint16_t speed);
void I2C_StartTransmission(uint8_t slave_address);
void I2C_RequestTransmission(uint8_t slave_address);
void I2C_WriteData(uint8_t device_address, uint8_t *data, uint8_t length);
void I2C_ReadData(uint8_t device_address,  uint8_t *data, uint8_t bytes_num);

#endif
