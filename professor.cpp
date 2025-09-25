#include <iostream>
#include "professor.h"


void professores::setLogin(std::string newLogin) {
    login = newLogin;
}
void professores::setSenha(std::string newSenha) {
    senha = newSenha;
}
void professores::setMatricula(int newMatricula) {
    matricula = newMatricula;
}
std::string professores::getLogin() {
    return login;
}
std::string professores::getSenha() {
    return senha;
}
int professores::getMatricula() {
    return matricula;
}