#ifndef SENSOR_H
#define SENSOR_H

#include <string.h>
#include <stdlib.h>

#define NOME_MAX      20
#define BUFFER_SIZE   10 

class Sensor {
    protected:
        char nome[NOME_MAX];
        float buffer1[BUFFER_SIZE];
        float buffer2[BUFFER_SIZE];
        int index1;
        int index2;
    public:
        void setNome(const char* newNome);
        const char* getNome();

        void adicionaBuffer1(float newData);
        float getBufferData1(int index);
        void adicionaBuffer2(float newData);
        float getBufferData2(int index);
        void clearBuffers();
        float getLastData1();
        float getLastData2();
        int getIndex();
};

#endif