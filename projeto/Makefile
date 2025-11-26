# ================================
# Configurações do sistema
# ================================
MCU       = atmega328p
F_CPU     = 16000000UL

CXX       = avr-g++
CC        = avr-gcc
OBJCOPY   = avr-objcopy
CXXFLAGS  = -std=c++17 -Wall -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU)
LDFLAGS   = -mmcu=$(MCU)

# Ajuste conforme seu programador
PROGRAMMER = arduino
PORT       = /dev/ttyUSB0
BAUD       = 115200


# ================================
# Arquivos do projeto
# ================================
SRC  = $(wildcard *.cpp)
OBJ  = $(SRC:.cpp=.o)
TARGET = main

# ================================
# Regras principais
# ================================
all: $(TARGET).hex

$(TARGET).elf: $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@


# ================================
# Upload via avrdude
# ================================
upload: $(TARGET).hex
	avrdude -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$(TARGET).hex:i


# ================================
# Limpeza
# ================================
clean:
	rm -f *.o *.elf *.hex

