#include <iostream>
#include "pessoa.h"

#define MAX_ALUNO   100

class alunos: public pessoa {
        int matricula;
        float nota1;
        float nota2;
    public:
        void setMatricula(int newMatricula);
        void setNota1(float newNota1);
        void setNota2(float newNota2);
        int getMatricula();
        float getNota1();
        float getNota2();
};
