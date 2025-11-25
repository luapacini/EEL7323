#ifndef Serial_H
#define Serial_H

#include <stdint.h>

#ifndef Serial1_H
    typedef enum {
        BAUDRATE_9600,
        BAUDRATE_115200
    } baudrate_t;
#endif

class Serial {
    public:
        void Init(baudrate_t baudrate);
        void println(const char *message);
        void print(const char *message);
        void hexprint_byte(uint8_t byte);
        uint8_t ReadByte();
        void TransmitByte(char data);
    private:
        char dec_to_hex(uint8_t dec);
};

#endif
