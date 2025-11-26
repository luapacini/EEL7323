#include "Sensor.h"
using namespace std;

void Sensor::setNome(const char* newNome){
    strncpy(nome, newNome, NOME_MAX - 1);
    nome[NOME_MAX - 1] = '\0';
}
const char* Sensor::getNome(){
    return nome;
}

void Sensor::adicionaBuffer1(float newBufferData) {
    if (index1 < BUFFER_SIZE) {
        buffer1[index1++] = newBufferData;
    }
}

float Sensor::getBufferData1(int index){
    return buffer1[index];
}

void Sensor::adicionaBuffer2(float newBufferData) {
    if (index2 < BUFFER_SIZE) {
        buffer2[index2++] = newBufferData;
    }
}

float Sensor::getBufferData2(int index){
    return buffer2[index];
}

void Sensor::clearBuffers() {
    index1 = 0;
    index2 = 0;
}

float Sensor::getLastData1() {
    return buffer1[index1];
}
float Sensor::getLastData2() {
    return buffer2[index2];
}

int Sensor::getIndex() {
    return index1;
}
