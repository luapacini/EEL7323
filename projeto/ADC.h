#pragma once

#include <stdint.h>

#define ADS1115_ADDRESS_GND 0x48 // ADS1115 default address (ADDR pin connected to GND)
#define ADS1115_ADDRESS_VDD 0x49 // ADDR pin connected to VDD
#define ADS1115_ADDRESS_SDA 0x4A // ADDR pin connected to SDA
#define ADS1115_ADDRESS_SCL 0x4B // ADDR pin connected to SCL

#define CONV_REGIST 0x00 // Conversion register address in the Address Pointer Register (00b)
#define CONFIG_REGIST 0x01 // Config register address in the Address Pointer Register (01b)
#define LO_THRESH_REGIST 0x02 // Lower threshold register Address in the Address Pointer Register (10b)
#define HI_THRESH_REGIST 0x03 // Higher threshold address in the Address Pointer Register (11b)

#define OS_MODE_OFF    0x00 // Sets the OS bit as 0 (has no effect when writing)
#define OS_MODE_SINGLE_SHOT 0x80 // Sets the OS bit as 1 to perform a conversion

#define ADC0_TO_ADC1 0x00 // Config the MUX to do the conversions using the ADC0 referenced to ADC1
#define ADC0_TO_ADC3 0x10 // Config the MUX to do the conversions using the ADC0 referenced to ADC3
#define ADC1_TO_ADC3 0x20 // Config the MUX to do the conversions using the ADC1 referenced to ADC3
#define ADC2_TO_ADC3 0x30 // Config the MUX to do the conversions using the ADC2 referenced to ADC3
#define ADC0_TO_GND    0x40 // Config the MUX to do the conversions using the ADC0 referenced to GND
#define ADC1_TO_GND    0x50 // Config the MUX to do the conversions using the ADC1 referenced to GND
#define ADC2_TO_GND    0x60 // Config the MUX to do the conversions using the ADC2 referenced to GND
#define ADC3_TO_GND    0x70 // Config the MUX to do the conversions using the ADC3 referenced to GND

#define PGA_GAIN_FSR_6_144V 0x00 // Sets the full scale resolution to +- 6.144 V
#define PGA_GAIN_FSR_4_096V 0x02 // Sets the full scale resolution to +- 4.096 V

#define CONTINUOUS_MODE 0x00 // Continuous mode condition (0b)
#define SINGLE_SHOT_MODE 0x01 // Single-shot mode (1b)

#define DATA_RATE_860 0xE0 // Sets the data rate acquisition to 860 SPS (860 Hz)

#define COMP_MODE_DEF 0x00 // Sets the comparator mode as default (traditional)
#define COMP_MODE_WIN 0x10 // Sets the comparator mode as window comparator

#define COMP_POL_LOW 0x00 // Sets the polarity of the ALERT/RDY pin as LOW (default)
#define COMP_POL_HIGH 0x01 // Sets the polarity of the ALERT/RDY pin as HIGH

#define COMP_LAT_OFF 0x00 // Sets the comparator latching as OFF
#define COMP_LAT_ON 0x01 // Sets the comparator latching as ON

#define COMP_QUE_OFF 0x03 // Disable the comparator and set the ALERT/RDY pin to high-impedance

#define BUFFER_SIZE 1 // Buffer size para media movel

class ADC {
    private:
        uint16_t conversion_constant = 0;
        uint16_t buffer[BUFFER_SIZE] = {0}; // Buffer declaration
        int buffer_idx = 0; // Buffer index declaration
        unsigned long sum = 0.0; // For the moving average
        uint16_t moving_average(uint16_t new_sample);
    public:
        void Init(uint8_t device_address, uint8_t channel, uint8_t gain, uint8_t mode, uint8_t data_rate, uint8_t comp_mode, uint8_t comp_pol, uint8_t comp_lat, uint8_t comp_que);
        uint32_t Read(uint8_t device_address);
};
