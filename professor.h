#include <iostream>
#include "pessoa.h"

#define MAX_PROF    10

class professores: public pessoa {
        std::string login;
        std::string senha;    
        int matricula;
    public:
        void setLogin(std::string newLogin);
        void setSenha(std::string newSenha);
        void setMatricula(int newMatricula);
        int getMatricula();
        std::string getLogin();
        std::string getSenha();
};