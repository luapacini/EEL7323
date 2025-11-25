#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/io.h>

#include "Serial.h"
#include "I2C.h"
#include "SHT30.h"
#include "ADC.h"
#include "Buzzer.h"
#include "LED.h"


volatile uint32_t diffTempo = 0;

int main ()
{
    cli();
    Serial::Init();

    ADC::Init(ADS1115_ADDRESS_GND, ADC0_TO_GND, PGA_GAIN_FSR_6_144V, CONTINUOUS_MODE, DATA_RATE_860, COMP_MODE_DEF, COMP_POL_LOW, COMP_LAT_OFF, COMP_QUE_OFF);

    SHT30 SHT30_1;
    ADC ADS1115;

    // uint16_t samples = 0;
    // uint32_t counter = 0;

    // uint32_t repeated = 0;

    // uint32_t voltage_val = 0;
    // uint32_t old_voltage = 0;

    //char buffer[10];

    DDRD |= (1 << PD5);
    // DDRB |= (1 << PB4);
    // DDRB |= (1 << PB3);

    SHT30_1.aquisitionSetup();
    SHT30_1.periodicAquisition();

    sei();

    while (true)
    {

        //PORTB &= ~(1 << PB5);
        snprintf(buffer, sizeof(buffer), "%u", (unsigned int) voltage_val);
        Serial::print("Tensão medida [mV]: ");
        Serial::println(buffer);

        snprintf(buffer, sizeof(buffer), "%u", (unsigned int) samples);
        Serial::print("Número de amostras: ");
        Serial::println(buffer);

        snprintf(buffer, sizeof(buffer), "%u", (unsigned int) repeated);
        Serial::print("Número de amostras repetidas: ");
        Serial::println(buffer);
    }
}
