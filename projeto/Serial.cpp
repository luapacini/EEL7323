#include "Serial.h"

#include <avr/io.h>
#include <util/delay.h>

#define BIT_CHECK(REG, BIT)      ((REG >> BIT) & 1)

// ---------------------------------------------------------------------------------------------------
// Serial Library code

void Serial::Init(baudrate_t baudrate) 
{
    switch (baudrate) {
    case BAUDRATE_9600:
        UBRR0H = 0;
        UBRR0L = 103;
        break;
    case BAUDRATE_115200:
        UBRR0H = 0;
        // UBRR0L = 8;
        UBRR0L = 16;
        UCSR0A |= (1<<1); // set U2X
        break;
    default: // Sets the baud rate to 9600 and keeps sending to serial that an error has happened
        UBRR0H = 0;
        UBRR0L = 103;
        while (1) {
            Serial::println("The selected BAUDRATE does not work.");
            _delay_ms(1000);
        }
    }

    //UCSR0B = (1<<TXEN0); // Enable transmitter
    UCSR0B = (1<<RXEN0) | (1<<TXEN0); // Enable receiver and transmitter

    UCSR0C = (1<<USBS0)|(3<<UCSZ00);// Set frame format: 8data, 2stop bit 
}

void Serial::TransmitByte(char data)
{
    /* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1<<UDRE0)) );
    /* Put data into buffer, sends the data */
    UDR0 = data;
}

void Serial::println (const char *message)
{
    while(*message) {
        Serial::TransmitByte(*message++);
    }
    Serial::TransmitByte('\r');
    Serial::TransmitByte('\n');
}

void Serial::print (const char *message)
{
    while(*message) {
        Serial::TransmitByte(*message++);
    }
}

char Serial::dec_to_hex(uint8_t dec)
{
    if(dec > 9)
        return 'A' + dec - 10;
    else
        return '0' + dec;
}

void Serial::hexprint_byte (uint8_t byte) 
{
    Serial::TransmitByte('0');
    Serial::TransmitByte('x');

    uint8_t low = byte & 0x0F;
    uint8_t high = (byte & 0xF0) >> 4;

    Serial::TransmitByte(dec_to_hex(high));
    Serial::TransmitByte(dec_to_hex(low));
    Serial::TransmitByte('\r');
    Serial::TransmitByte('\n');
}

uint8_t Serial::ReadByte()
{
    uint8_t delay = 200;

    while ((BIT_CHECK(UCSR0A, RXC0) == 0) && (delay > 0)) {
        delay--;
        _delay_us(10);
    }

    if (delay == 0)
    {
        return 0;
    }

    return UDR0;
}
