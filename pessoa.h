#include <iostream>
#include <string>

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
