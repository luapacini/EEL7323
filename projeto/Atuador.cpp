#include "Atuador.h"

void Atuador::setNome(const char* newNome) {
    strncpy(nome, newNome, NOME_MAX - 1);
    nome[NOME_MAX - 1] = '\0'; 
}
const char* Atuador::getNome() const {
    return nome;
}