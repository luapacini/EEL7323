#include <iostream>
#include "pessoa.h"

class pessoa {
        char atributo1[10];
        char atributo2[10];    
        char nome[10];
    public:
        void setAtributo1(char newAtributo1[10]);
        void setAtributo2(char newAtributo2[10]);
        void setNome(char newNome[10]);
        char getNome();
        char getAtributo1();
        char getAtributo2();
};

void pessoa::setNome(char newNome[10]) {
    for (int i=0; i<10; i++) {
        nome[i] = newNome[i];
    }
}
void pessoa::setAtributo1(char newAtributo1[10]) {
    for (int i=0; i<10; i++) {
        atributo1[i] = newAtributo1[i];
    }
}
void pessoa::setAtributo2(char newAtributo2[10]) {
    for (int i=0; i<10; i++) {
        atributo2[i] = newAtributo2[i];
    }
}