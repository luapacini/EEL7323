#include <iostream>
#include "pessoa.h"

class pessoa {
        std::string atributo1;
        std::string atributo2;    
        std::string nome;
    public:
        void setAtributo1(std::string newAtributo1);
        void setAtributo2(std::string newAtributo2);
        void setNome(std::string newNome);
        std::string getNome();
        std::string getAtributo1();
        std::string getAtributo2();
};

void pessoa::setNome(std::string newNome) {
    for (int i=0; i<10; i++) {
        nome[i] = newNome[i];
    }
}
void pessoa::setAtributo1(std::string newAtributo1) {
    for (int i=0; i<10; i++) {
        atributo1[i] = newAtributo1[i];
    }
}
void pessoa::setAtributo2(std::string newAtributo2) {
    for (int i=0; i<10; i++) {
        atributo2[i] = newAtributo2[i];
    }
}

std::string pessoa::getNome() {
    return nome;
}

std::string pessoa::getAtributo1() {
    return atributo1;
}

std::string pessoa::getAtributo2() {
    return atributo2;
}