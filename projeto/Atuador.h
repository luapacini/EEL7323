#ifndef ATUADOR_H
#define ATUADOR_H

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <vector>

using namespace std;

class Atuador {
    protected:
        string nome;
    public:
        void setNome(string newNome);
        string getNome();
};

#endif