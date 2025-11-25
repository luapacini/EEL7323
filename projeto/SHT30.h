#include <stdint.h>

#define SHT30_ADDRESS 0x44


uint8_t crc8(uint8_t *msg, int lengthOfMsg, uint8_t init);

void periodicAquisitionSetup();

uint8_t periodicAquisition();

uint8_t periodicAquisitionBreak();

void oneShotAquisitionSetup();

void oneShotAquisition();
