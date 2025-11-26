#ifndef SENSOR_H
#define SENSOR_H

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <vector>

using namespace std;

class Sensor {
    protected:
        string nome;
        vector<float> buffer1;
        vector<float> buffer2;
    public:
        void setNome(string newNome);
        string getNome();

        void adicionaBuffer1(float newData);
        vector<float> getBufferData1();
        void adicionaBuffer2(float newData);
        vector<float> getBufferData2();
        void clearBuffers();
};

#endif