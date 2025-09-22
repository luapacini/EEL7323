/* Online C++ Compiler and Editor */
#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;

class contaBancaria {
        int numero;
        float saldo;
        float taxa;
    public:
        // contaBancaria();
        //~contaBancaria();
        void deposito(float valorDeposito);
        void saque(float valorSaque);
        float retornaSaldo();
};

class sistemaUsuario {
        string nome;
        string senha;
        char acesso;
    public:
        // sistemaUsuario(string nomeUsuario, string senhaUsuario, char acessoUsuario);
        void atribuiNome(string nomeUsuario);
        void atribuiSenha(string senhaUsuario);
        void atribuiAcesso(string acessoUsuario);
};

// contaBancaria::contaBancaria() {
//     saldo = 0.0;
// }

void contaBancaria::deposito(float valorDeposito) {
    saldo += valorDeposito;
}

void contaBancaria::saque(float valorSaque) {
    if (saldo >= valorSaque) {
        saldo -= valorSaque;
    } else {
        cout << "Operacao negada";
    } 
}

float contaBancaria::retornaSaldo() {
    return saldo;
}

int main()
{
   contaBancaria conta1;
   
   std::cout << conta1.retornaSaldo();
   
  int menu = 0;
  float auxSaque, auxDeposito;
  
  cout << "digite: 1 para deposito, 2 para saque, 3 para consulta de saldo" << endl;
  cin >> menu;
  
  while(true) {
      
    switch (menu) {
      case 1:
        cout << endl << "insira o valor a ser depositado: ";
        cin >> auxDeposito;
        conta1.deposito(auxDeposito);
        cout << endl << "o saldo atual eh: " << conta1.retornaSaldo() << endl;
        menu = 4;
        break;
        
      case 2:
        cout << "insira o valor a ser sacado: " << endl;
        cin >> auxSaque;
        conta1.saque(auxSaque);
        cout << endl << "o saldo atual eh: " << conta1.retornaSaldo() << endl;
        menu = 4;
        break;
      
      case 3:
        cout << "o saldo atual eh: " <<conta1.retornaSaldo() << endl;
        menu = 4;
        break;
        
      case 4:
        cout << "digite: 1 para deposito, 2 para saque, 3 para consulta de saldo" << endl;
        cin >> menu;
        break;
        
      default:
        cout << "nao eh uma opcao" << endl;
        menu = 4;
        break;
    }
  }
   return 0;
}