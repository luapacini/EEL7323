#include "Serial_0.h"
#include "ADS.h"
#include "I2C.h"
#include "Timer1.h"
#include "WDT.h"
#include "SHT30.h"
#include "ICP.h"
#include "PWM.h"
#include "Counter0.h"

#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/io.h>
volatile uint32_t diffTempo = 0;

int main ()
{
    cli();
    Serial_0_Init(BAUDRATE_115200);

    //PWMConfig();


    //ADS_Init(ADS1115_ADDRESS_GND, ADC0_TO_GND, PGA_GAIN_FSR_6_144V, CONTINUOUS_MODE, DATA_RATE_860, COMP_MODE_DEF, COMP_POL_LOW, COMP_LAT_OFF, COMP_QUE_OFF);

    // uint16_t samples = 0;
    // uint32_t counter = 0;

    // uint32_t repeated = 0;

    // uint32_t voltage_val = 0;
    // uint32_t old_voltage = 0;

    //char buffer[10];

    DDRD |= (1 << PD5);
    // DDRB |= (1 << PB4);
    // DDRB |= (1 << PB3);

    // Timer1_Init();
    // Timer0_Init();

    //WDT_Prescaler_Change();

    //periodicAquisitionSetup();
    //periodicAquisition();
    //oneShotAquisitionSetup();
    //oneShotAquisition();

    // tratadorICP::ICPConfig();

    sei();

    Serial_0_println("Entrando no while true");

    while (true)
    {
    //     //PORTB ^= (1 << PB3); // Sets the pin 11 arudino as ONE

    //     samples = 0; 
    //     counter = 0;
    //     repeated = 0;
    //     old_voltage = 0;
    //     //----- teste interrupcao
    //     if(tratadorICP::confereFlag()) { //imprime na serial caso interrupcao 
    //         diffTempo = tratadorICP::retornaDiff();
    //         //Serial_0_println("interrupcao");
    //         snprintf(buffer, sizeof(buffer), "%lu",  diffTempo);
    //         Serial_0_print("microssegundos desde a ultima interrupcao: "); Serial_println(buffer); Serial_println(" ");
    //     }

        // PORTD &= ~(1 << PD5); // Sets the pin 13 arudino as ONE
        // _delay_ms(500);
        
        PORTD |= (1 << PD5);
        _delay_ms(1000);
        PORTD &= ~(1 << PD5);
        _delay_ms(1000);
        Serial_0_println("loop"); 
    //     while (counter < 320)
    //     {
    //         if (Timer1_CheckFlag())
    //         {
    //             Timer1_ClearFlag();
    //             PORTB |= (1 << PB4); // Sets the pin 12 arudino as ONE
    //             voltage_val = ADS_Read(ADS1115_ADDRESS_GND);

    //             if (voltage_val == old_voltage)
    //             {
    //                 repeated++;
    //             }
 
    //             old_voltage = voltage_val;
    //             samples++;
    //             counter++;

    //             PORTB &= ~(1 << PB4);
    //         }
    //     }

        //PORTB &= ~(1 << PB5);
        /*snprintf(buffer, sizeof(buffer), "%u", (unsigned int) voltage_val);
        Serial_0_print("Tensão medida [mV]: ");
        Serial_0_println(buffer);

        snprintf(buffer, sizeof(buffer), "%u", (unsigned int) samples);
        Serial_0_print("Número de amostras: ");
        Serial_0_println(buffer);

        snprintf(buffer, sizeof(buffer), "%u", (unsigned int) repeated);
        Serial_0_print("Número de amostras repetidas: ");
        Serial_0_println(buffer);*/

        //periodicAquisition();
        //watchdogReset();

        /*if (breakFlag == 0) {
            Serial_0_println(""); Serial_println("");
        }

        if(k == 100 && breakFlag != 1) {
            breakFlag = periodicAquisitionBreak(); //provisorio para teste do break, sofisticar solucao dps (interrupcao?)
        }*/
        //_delay_ms(3000);

        //_delay_ms(500);
    }
}
