#include <iostream>
#include "clockCalendar.h"
#include "pessoa.h"
#include "professor.h"
#include "aluno.h"

using namespace std;

class cadastroAlunos {
        alunos aluno[MAX_ALUNO];
        ClockCalendar dataHora[MAX_ALUNO];
        bool valido[MAX_ALUNO];
    public:
        cadastroAlunos();
        bool getFlag(int indice);
        void setFlag(bool newFlag, int indice);
};

class cadastroProfessores {
        professores professor[MAX_PROF];
        ClockCalendar dataHora[MAX_PROF];
        bool valido[MAX_PROF];
    public:
        cadastroProfessores();
        bool getFlag(int indice);
        void setFlag(bool newFlag, int indice);
};

cadastroProfessores::cadastroProfessores() {

}
bool cadastroProfessores::getFlag(int indice){
    return valido[indice];
}
void cadastroProfessores::setFlag(bool newFlag, int indice) {
    valido[indice] = newFlag;
}

cadastroAlunos::cadastroAlunos(){

}

bool cadastroAlunos::getFlag(int indice){
    return valido[indice];
}
void cadastroAlunos::setFlag(bool newFlag, int indice) {
    valido[indice] = newFlag;
}

using namespace std;

int main()
{
   int auxMatricula, auxSwitch, auxSenha, auxLogin;
   int auxProf = 0;
   int auxAluno = 0;
   float auxNota1, auxNota2;
   bool flagLogin = false;


   cadastroAlunos cadastroAluno;
   cadastroProfessores cadastroProf;
     
   cout << "Digite:\n"
            "1 para login\n"
            "2 para logout\n"
            "3 para incluir aluno"
            "4 para excluir aluno"
            "5 para alterar aluno"
            "6 para consultar aluno"
            "7 para listar alunos"
            "8 para incluir professor"
            "9 para excluir professor"
            "10 para alterar professor"
            "11 para consultar professor"
            "12 para listar professores";
   cin >> auxSwitch;
   
   switch (auxSwitch) {

       case 1: //login
            if(flagLogin && auxProf != 0) {
                cout << "ja existe outro login ativo\n";
            } else if (!flagLogin && auxProf >0) {
                cout << "login: ";
                cin >> auxLogin;
                cout << "senha: ";
                cin >> auxSenha;
                //aqui usar map pra ver se existe cadastro
                for(int i = 0; i<MAX_PROF; i++) {
                    if(auxLogin == cadastroProf.getLogin() && auxSenha == cadastroProf[i].getSenha()) {
                        flagLogin = true;
                        break;
                    } 
                }                
            } else if (!flagLogin && auxProf == 0) {
                cout << "nenhum professor cadastrado, digite 8 para incluir um novo professor";
            }
            auxSwitch++;
            break;

       case 2: //logout
            if(auxProf > 0) {
                if (!flagLogin) cout << "nenhum login ativo";
            } else cout << "nenhum professor cadastrado, digite 8 para incluir um novo professor";
            flagLogin = false;
            break;

       case 3: //incluir aluno
       if(auxProf > 0) {
            if (auxAluno < MAX_ALUNO) {
                cout << "Matricula: ";
                cin >> auxMatricula;
                cout << "Nota 1: ";
                cin >> auxNota1;
                cout << "Nota 2: ";
                cin >> auxNota2;
                
                aluno[auxAluno].setMatricula(auxMatricula);
                aluno[auxAluno].setNota1(auxNota1);
                aluno[auxAluno].setNota2(auxNota2);

                auxAluno++;
            } else {
                cout << "limite de alunos atingidos";
            }
            } else cout << "nenhum professor cadastrado, digite 8 para incluir um novo professor";
            auxSwitch++;
            break;

        case 4: //excluir aluno
            if(auxProf > 0) {
            } else cout << "nenhum professor cadastrado, digite 8 para incluir um novo professor";
            auxSwitch++;
            break;

        case 5: //alterar aluno
            if(auxProf > 0) {
                cout << "matricula: ";
                cin >> auxMatricula;
                //usar map pra achar o aluno de tal matricula
                cout << "nota 1: ";
                cin >> auxNota1;
                cout << "nota 2: ";
                cin >> auxNota2;

                aluno[/*qual?*/].setNota1(auxNota1);
                aluno[/*qual?*/].setNota2(auxNota2);
            } else cout << "nenhum professor cadastrado, digite 8 para incluir um novo professor";

            auxSwitch++;
            break;

        case 6: //consultar aluno
            if(auxProf > 0) {
                cout << "Insira a matricula: ";
                cin >> auxMatricula;
                //errado isso arrumar por map
                cout << "nota 1: " << aluno[auxAluno].getNota1() << endl;
                cout << "nota 2: " << aluno[auxAluno].getNota2() << endl;
            } else cout << "nenhum professor cadastrado, digite 8 para incluir um novo professor";

            auxSwitch++;
            break;

        case 7: //listar alunos
            if(auxProf > 0) {
                for (int i=0; i<auxAluno;i++) {
                    cout << "matricula aluno " << i << ": " << aluno[auxAluno].getMatricula() << endl;
                    cout << "nota 1aluno " << i << ": " << aluno[auxAluno].getNota1() << endl;
                    cout << "nota 2 aluno " << i << ": " << aluno[auxAluno].getNota2() << endl;
                }
            } else cout << "nenhum professor cadastrado, digite 8 para incluir um novo professor";

            auxSwitch++;
            break;

        case 8: //incluir professor
            if (auxProf < MAX_PROF) {
                cout << "login: ";
                cin >> auxLogin;
                cout << "senha: ";
                cin >> auxSenha;
            
                professor[auxProf].setLogin(auxLogin);
                professor[auxProf].setSenha(auxSenha);
                
                auxProf++;
            } else {
                cout << "limite de professores atingidos";
            }
            
            auxSwitch++;
            break;

        case 9: //excluir professor
            if(auxProf > 0) {
                //adicionar destrutor e chamar aqui
            } else cout << "nenhum professor cadastrado, digite 8 para incluir um novo professor";

            auxSwitch++;
            break;

        case 10: //alterar professor
            if(auxProf > 0) {
                cout << "matricula: ";
                cin >> auxMatricula;
                //usar map pra achar o professor de tal matricula
                cout << "login: ";
                cin >> auxLogin;
                cout << "senha: ";
                cin >> auxSenha;

                professor[/*qual?*/].setLogin(auxLogin);
                professor[/*qual?*/].setSenha(auxSenha);
            } else cout << "nenhum professor cadastrado, digite 8 para incluir um novo professor";

            auxSwitch++;
            break;

        case 11: //consultar professor
            if(auxProf > 0) {
                cout << "matricula: ";
                cin >> auxMatricula;
                //usar map pra achar o professor de tal matricula
                //nao sei que opcoes listar? nao vou listar login e senha ne?
            } else cout << "nenhum professor cadastrado, digite 8 para incluir um novo professor";

            auxSwitch++;
            break;

        case 12: //listar professores
            if(auxProf > 0) {
                if (flagLogin) {
                    for (int i=0; i<auxProf;i++) {
                        cout << "matricula professor " << i << ": " << professor[auxProf].getMatricula() << endl;
                    }
                } else cout << "nenhum login ativo";
            } else cout << "nenhum professor cadastrado, digite 8 para incluir um novo professor";

            auxSwitch++;
            break;
        default:
                cout << "Nao eh uma opcao\n";
                auxSwitch=1;        
   }
   return 0;
}