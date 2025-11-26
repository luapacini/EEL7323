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
#include "LDR.h"

#define AQUISICOES_POR_CICLO 10
#define PERIODO_MS 60000  // 60s

void salvarCSV(SHT30 &sht, LDR &ldr) {
    bool arquivoExiste = (fopen("log.csv", "r") != NULL);

    FILE *fp = fopen("log.csv", "a"); 
    if (!fp) return;

    // só escreve cabeçalho se for a primeira criação do arquivo
    if (!arquivoExiste) {
        fprintf(fp, "Amostra,Temperatura,Umidade,Luminosidade\n");
    }

    vector<float> temps = sht.getBufferData1();
    vector<float> hums  = sht.getBufferData2();
    vector<float> lums  = ldr.getBufferData1();

    for (int i = 0; i < temps.size(); i++) {
        fprintf(fp, "%d,%.2f,%.2f,%.2f\n",
                i+1, temps[i], hums[i], lums[i]);
    }

    fclose(fp);
    Serial::println("CSV atualizado.");
}

void salvarCSVexcecao(SHT30 &sht, LDR &ldr) {
    bool arquivoExiste = (fopen("excecao.csv", "r") != NULL);

    FILE *fp = fopen("excecao.csv", "a"); 
    if (!fp) return;

    // só escreve cabeçalho se for a primeira criação do arquivo
    if (!arquivoExiste) {
        fprintf(fp, "Temperatura,Umidade,Luminosidade\n");
    }

    vector<float> temps = sht.getBufferData1();
    vector<float> hums  = sht.getBufferData2();
    vector<float> lums  = ldr.getBufferData1();

    for (int i = 0; i < temps.size(); i++) {
        fprintf(fp, "%.2f,%.2f,%.2f\n",
                temps[i], hums[i], lums[i]);
    }

    fclose(fp);
}

void rotinaEmergencia(const char* tipo,
                      float valorCritico,
                      Sensor& sht,
                      Sensor& ldr,
                      Buzzer& buzzer)
{
    Serial::println("=== ALERTA DE VALOR CRITICO ===");
    Serial::print("Variavel: ");
    Serial::println(tipo);
    Serial::print("Valor critico detectado: ");
    Serial::println(valorCritico);

    salvarCSVexcecao(sht, ldr)

    sht.clearBuffers();
    ldr.clearBuffers();

    buzzer.ligar();

    for (int i = 0; i < 10; i++) {
        _delay_ms(1000);  
    }

    buzzer.desligar();
}


// ---------------------------------------------------------

int main() {
    cli();
    Serial::Init();
    I2C::Init();

    ADC::Init(ADS1115_ADDRESS_GND, ADC0_TO_GND, PGA_GAIN_FSR_6_144V, CONTINUOUS_MODE, DATA_RATE_860, COMP_MODE_DEF, COMP_POL_LOW, COMP_LAT_OFF, COMP_QUE_OFF);
    
    sei();

    SHT30 sht;
    LDR ldr;

    sht.setNome("SHT30");
    ldr.setNome("LDR");

    // Configuração inicial
    sht.setModoAquisicao(true);  // periodic mode
    sht.aquisitionSetup();

    int contador = 0;
    bool estadoCritico = false;

    while (true) {

        try {

            sht.periodicAquisition();
            ldr.calcularLuminosidade();
        
            float t = sht.getBufferData1().back();   // última temperatura adicionada
            float h = sht.getBufferData2().back();   // última umidade adicionada
            float l = ldr.getBufferData1().back();   // última luminosidade adicionada
    
            contador++;
    
            Serial::print("Aquisicao "); 
            Serial::print(contador);
            Serial::print(":  Temp = ");
            Serial::print(t);
            Serial::print(" °C | Umidade = ");
            Serial::print(h);
            Serial::print(" % | Luminosidade = ");
            Serial::print(l);
            Serial::println(" %");
    
            // ---------------- SALVAR CSV -------------------
            if (contador >= AQUISICOES_POR_CICLO) {
    
                Serial::println("");
                Serial::println("10 amostras atingidas. Salvando CSV...");
                salvarCSV(sht, ldr);
    
                contador = 0;
                sht.clearBuffers();
                ldr.clearBuffers();
            }
        }
        catch (const LuminosidadeException& e) {
            rotinaEmergencia(e.what(), ldr.getBuffer1().back(), sht, ldr, buzzer);
        }
        catch (const TemperaturaException& e) {
            rotinaEmergencia(e.what(), sht.getBuffer1().back(), sht, ldr, buzzer);
        }
        catch (const UmidadeException& e) {
            rotinaEmergencia(e.what(), sht.getBuffer2().back(), sht, ldr, buzzer);
        }

        // Espera o próximo ciclo (60 s)
        for (int i = 0; i < 60; i++) _delay_ms(1000);
    }
    return 0;
}
