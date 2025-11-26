#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/io.h>

#include "Serial.h"
#include "I2C.h"
#include "SHT30.h"
#include "ADC1.h"
#include "Buzzer.h"
#include "LED.h"
#include "LDR.h"
#include "RegistroCSV.h"

#define AQUISICOES_POR_CICLO 10
#define PERIODO_MS 60000  // 60s

template <typename T, size_t N>
class Media {
public:
    // Calcula a média
    static T calcular(const T (&valores)[N]) {
        if (N == 0) return T(); // evita divisão por zero

        T soma = 0;
        for (size_t i = 0; i < N; ++i) {
            soma += valores[i];
        }
        return soma / N;
    }
};

bool rotinaEmergencia(SHT30& sht, LDR& ldr, Buzzer& buzzer)
{
    Serial::println("=== ALERTA DE VALOR CRITICO ===");

    salvarCSVexcecao(sht, ldr);

    sht.clearBuffers();
    ldr.clearBuffers();

    buzzer.ligar();

    for (int i = 0; i < 10; i++) {
        _delay_ms(1000);  
    }

    buzzer.desligar();

    return false;
}

// ---------------------------------------------------------

int main() {
    cli();
    Serial::Init();
    
    sei();
    
    SHT30 sht;
    LDR ldr;
    ADC1 adc1;
    Buzzer buzzer(100, false);
    LED led;

    adc1.Init(ADS1115_ADDRESS_GND, ADC0_TO_GND, PGA_GAIN_FSR_6_144V, CONTINUOUS_MODE, DATA_RATE_860, COMP_MODE_DEF, COMP_POL_LOW, COMP_LAT_OFF, COMP_QUE_OFF);

    sht.setNome("SHT30");
    ldr.setNome("LDR");

    // Configuração inicial
    sht.setModoAquisicao(true);  // periodic mode
    sht.aquisitionSetup();

    int contador = 0;
    bool estadoCritico = false;
    char auxbuffer[10];

    while (true) {

        sht.periodicAquisition();
        ldr.calcularLuminosidade();
    
        float t = sht.getLastData1();   // última temperatura adicionada
        float h = sht.getLastData2();   // última umidade adicionada
        float l = ldr.getLastData1();   // última luminosidade adicionada

        ldr.ajustarLED(led, estadoCritico);
        
        if(t>45 || t<10 || h>90 || h<40) estadoCritico = true;

        if (estadoCritico) {
            estadoCritico = rotinaEmergencia(sht, ldr, buzzer);
        }

        contador++;

        Serial::print("Aquisicao ");
        snprintf(auxbuffer, 10, "%u", (unsigned int)(contador));
        Serial::print(auxbuffer);
        Serial::print(":  Temp = ");
        snprintf(auxbuffer, 10, "%u", (unsigned int)(t));
        Serial::print(auxbuffer);
        Serial::print(" °C | Umidade = ");
        snprintf(auxbuffer, 10, "%u", (unsigned int)(h));
        Serial::print(auxbuffer);
        Serial::print(" % | Luminosidade = ");
        snprintf(auxbuffer, 10, "%u", (unsigned int)(l));
        Serial::print(auxbuffer);
        Serial::println(" %");

        // ---------------- SALVAR CSV -------------------
        if (contador >= AQUISICOES_POR_CICLO) {
            contador = 0;
            sht.clearBuffers();
            ldr.clearBuffers();
        }
    }

    // Espera o próximo ciclo (60 s)
    for (int i = 0; i < 60; i++) _delay_ms(1000);
    
    return 0;
}
