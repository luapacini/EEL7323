#include "Sensor.h"
using namespace std;

void Sensor::setNome(string newNome){
    nome = newNome;
}
string Sensor::getNome(){
    return nome;
}

void Sensor::adicionaBuffer1(float newBufferData) {
    buffer1.push_back(newBufferData);
}

vector<float> Sensor::getBufferData1(){
    return buffer1;
}

void Sensor::adicionaBuffer2(float newBufferData) {
    buffer2.push_back(newBufferData);
}

vector<float> Sensor::getBufferData2(){
    return buffer2;
}

void Sensor::clearBuffers() {
    buffer1.clear();
    buffer2.clear();
}

