#ifndef Serial_H
#define Serial_H

#include <stdint.h>

class Serial {
    private:
        char dec_to_hex(uint8_t dec);
    public:
        void Init();
        void println(const char *message);
        void print(const char *message);
        uint8_t ReadByte();
        void TransmitByte(char data);
};

#endif
