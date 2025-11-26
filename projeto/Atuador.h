#ifndef ATUADOR_H
#define ATUADOR_H

#include <string.h>
#include <stdlib.h>

#define NOME_MAX 20

class Atuador {
    protected:
        char nome[NOME_MAX];
    public:
        void setNome(const char* newNome);
        const char* getNome() const;
};

#endif