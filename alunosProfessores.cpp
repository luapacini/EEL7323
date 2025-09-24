#include <iostream>

using namespace std;

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

class professores: public pessoa {
        char login[10];
        char senha[10];    
        int matricula;
    public:
        void setLogin(char newLogin[10]);
        void setSenha(char newSenha[10]);
        void setMatricula(int newMatricula[10]);
        int getMatricula();
        char getLogin();
        char getSenha();
};

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

class Clock {
   protected:
      int hr, min, sec, isPm;
   public:
      Clock (int h, int s, int m, int pm){
           hr = h;
           min = m;
           sec = s;
           isPm = pm;
      }
      void setClock (int h, int m, int s, int pm){
           hr = h;
           min = m;
           sec = s;
           isPm = pm;
      }
      void readClock (int& h, int& m, int& s, int& pm){
           h = hr;
           m = min;
           s = sec;
           pm = isPm;
      }
      void advance (){
         if (sec < 59)
            sec++;
         else {
            sec = 0;
            if (min < 59)
               min++;
            else {
               min = 0;
               if (hr < 12)
                  hr++;
               else {
                  hr = 0;
               }
            }
         }
      }
};

class Calendar {
   protected:
      int mo, day, yr;
   public:
      Calendar (int m, int d, int y){
        mo = m;
        day = d;
        yr = y;
      }
      void setCalendar (int m, int d, int y){
        mo = m;
        day = d;
        yr = y;
      }
      void readCalendar (int& m, int& d, int& y){
        m = mo;
        d = day;
        y = yr;
      }
      void advance (){};
};

class ClockCalendar : public Clock, public Calendar {
   public:
      ClockCalendar (int mt, int d, int y, int h, int m, int s, int pm);
      void advance ();
};

ClockCalendar::ClockCalendar (int mt, int d, int y, int h, int m, int s, int pm) : Clock (h, m, s, pm), Calendar (mt, d, y){
}

void ClockCalendar::advance (){ // avancar o calendario, caso o clock
   int wasPm = isPm;       // mude de AM para PM.
   Clock::advance();
   if (wasPm && !isPm)
      Calendar::advance();
}

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

void professores::setLogin(char newLogin[10]) {
    for (int i=0; i<10; i++) {
        login[i] = newLogin[i];
    }
}
void professores::setSenha(char newSenha[10]) {
    for (int i=0; i<10; i++) {
        senha[i] = newSenha[i];
    }
}
void professores::setMatricula(int newMatricula[10]) {
    for (int i=0; i<10; i++) {
        matricula[i] = newMatricula[i];
    }
}
char professores::getLogin() {
    return login[10];
}
char professores::getSenha() {
    return senha[10];
}
int professores::getMatricula() {
    return matricula;
}

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

using namespace std;

int main()
{
   alunos aluno[100];
   professores professor[10];
   ClockCalendar dataHora[10];
   int auxMatricula, auxSwitch, auxSenha, auxLogin;
   int auxProf = 0;
   int auxAluno = 0;
   float auxNota1, auxNota2;
   bool flagLogin = false;
   
//    for (int i=0; i<4; i++) {
//         cout << "Matricula: ";
//         cin >> auxMatricula;
//         cout << "Nota 1: ";
//         cin >> auxNota1;
//         cout << "Nota 2: ";
//         cin >> auxNota2;
        
//         aluno[i].setMatricula(auxMatricula);
//         aluno[i].setNota1(auxNota1);
//         aluno[i].setNota2(auxNota2);
//    }
   
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
                flagLogin = true;
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
            if (auxAluno < 100) {
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
            if (auxProf < 10) {
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