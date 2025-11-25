#ifndef Serial_H
#define Serial_H

#include <stdint.h>

#define BIT_CHECK(REG, BIT)      ((REG >> BIT) & 1)

class Serial {
    private:
        char dec_to_hex(uint8_t dec);
    public:
        static void Init();
        static void println(const char *message);
        static void print(const char *message);
        static uint8_t ReadByte();
        static void TransmitByte(char data);
};

#endif
