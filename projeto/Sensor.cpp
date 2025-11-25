#include "Sensor.h"
using namespace std;

void Sensor::setNome(string newNome){
    nome = newNome;
}
string Sensor::getNome(){
    return nome;
}

void Sensor::adicionaBuffer(float newBufferData) {
    buffer.push_back(newBufferData);
}

vector<float> Sensor::getBufferData(){
    return buffer;
}


