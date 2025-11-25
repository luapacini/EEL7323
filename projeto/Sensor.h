#ifndef SENSOR_H
#define SENSOR_H

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <vector>

using namespace std;

class Sensor {
    private:
        string nome;
        vector<float> buffer;
    public:
        void setNome(string newNome);
        string getNome();

        void adicionaBuffer(float newData);
        vector<float> getBufferData();
};

#endif