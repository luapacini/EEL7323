#ifndef I2C_H
#define I2C_H

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

#ifndef TWSR0
    #undef  TWBR0
    #define TWBR0  TWBR
    #define TWSR0  TWSR
    #define TWAR0  TWAR
    #define TWDR0  TWDR
    #define TWCR0  TWCR
    #define TWAMR0 TWAMR
#endif


#define BIT_SET(REG, BIT)        REG |=  (1<<BIT)
#define BIT_CLEAR(REG, BIT)      REG &= ~(1<<BIT)

#define BIT_CHECK(REG, BIT)      ((REG >> BIT) & 1)

class I2C {
    private:
        static bool TimeOut(); 
        static void SendStart();
        static void SendStop();
        static void WriteDataByte(uint8_t data);
        static uint16_t ReadDataByte(bool ack);
    public:
        static void Init(uint16_t speed);
        static void StartTransmission(uint8_t slave_address);
        static void RequestTransmission(uint8_t slave_address);
        static void WriteData(uint8_t device_address, uint8_t *data, uint8_t length);
        static void ReadData(uint8_t device_address,  uint8_t *data, uint8_t bytes_num);
};

#endif
