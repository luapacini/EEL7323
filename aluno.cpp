#include <iostream>
#include "aluno.h"

void alunos::setMatricula(int newMatricula) {
    matricula = newMatricula;
}

void alunos::setNota1(float newNota1) {
    nota1 = newNota1;
}

void alunos::setNota2(float newNota2) {
    nota2 = newNota2;
}

int alunos::getMatricula() {
    return matricula;
}

float alunos::getNota1() {
    return nota1;
}

float alunos::getNota2() {
    return nota2;
}
