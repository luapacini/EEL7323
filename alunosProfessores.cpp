#include <iostream>

using namespace std;

class pessoa {
        char nome[10];    
        int diaNascimento;
        int mesNascimento;
        int anoNascimento;
    public:
        void setNome(char newNome);
        void setDiaNascimento(int newDia);
        void setMesNascimento(int newMes);
        void setAnoNascimento(int newAno);
        void getNome();
        void getDiaNascimento();
        void getMesNascimento();
        void getAnoNascimento();
};

class professores: public pessoa {
        char login[10];
        char senha[10];
        char disciplina[10];
    public:
        void setLogin(char newLogin);
        void setSenha(char newSenha);
        void setDisciplina(char newDisciplina);
        void getLogin();
        void getSenha();
        void getDisciplina();
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

void pessoa::setNome(char newNome) {
    nome = newNome;
}

void pessoa::setDiaNascimento(int newDia) {
    diaNascimento = newDia;
}

void pessoa::setMesNascimento(int newMes) {
    mesNascimento = newMes;
}

void pessoa::setAnoNascimento(int newAno) {
    anoNascimento = newAno;
}

void professores::setLogin(char newLogin) {
    login = newLogin;
}

void professores::setSenha(char newSenha) {
    senha = newSenha;
}

void professores::setDisciplina(char newDisciplina) {
    disciplina = newDisciplina;
}

void professores::getLogin() {
    return login;
}

void professores::getSenha() {
    return senha;
}

void professores::getDisciplina() {
    return disciplina;
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
   alunos aluno[4];
   int auxMatricula, auxSwitch;
   float auxNota1, auxNota2;
   
   for (int i=0; i<4; i++) {
        cout << "Matricula: ";
        cin >> auxMatricula;
        cout << "Nota 1: ";
        cin >> auxNota1;
        cout << "Nota 2: ";
        cin >> auxNota2;
        
        aluno[i].setMatricula(auxMatricula);
        aluno[i].setNota1(auxNota1);
        aluno[i].setNota2(auxNota2);
   }
   
   cout << "Digite:\n"
            "1 para listagem de alunos\n"
            "2 para consultar aluno\n"
            "3 para alterar dados de aluno";
   cin >> auxSwitch;
   
   switch (auxSwitch) {
       case 1:
            for(int i=0; i<4; i++) {
                cout << "Matricula: " << aluno[i].getMatricula() << endl;
                cout << "Nota 1: " << aluno[i].getNota1() << endl;
                cout << "Nota 2: " << aluno[i].getNota2() << endl;
            }
            auxSwitch++;
            break;
       case 2:
            cout << "Insira a matricula: ";
            cin >> auxMatricula;
            for (int i=0; i<3; i++) {
                if (auxMatricula == aluno[i].getMatricula()) {
                    cout << "Nota 1: " << aluno[i].getNota1() << endl;
                    cout << "Nota 2: " << aluno[i].getNota2() << endl;
                    continue;
                }
                if((i==3 && auxMatricula != aluno[i].getMatricula()) || auxMatricula == aluno[i].getMatricula()) cout << "Matricula nao encontrada.\n";
            }
            auxSwitch++;
            break;
       case 3:
            cout << "Insira a matricula: ";
            cin >> auxMatricula;
            for (int i=0; i<4; i++) {
                if (auxMatricula == aluno[i].getMatricula()) {
                    cout << "Matricula: ";
                    cin >> auxMatricula;
                    cout << "Nota 1: ";
                    cin >> auxNota1;
                    cout << "Nota 2: ";
                    cin >> auxNota2;
        
                    aluno[i].setMatricula(auxMatricula);
                    aluno[i].setNota1(auxNota1);
                    aluno[i].setNota2(auxNota2);
                }
            }
            auxSwitch++;
            break;
        default:
                cout << "Nao eh uma opcao\n";
                auxSwitch=1;
        
   }
   return 0;
}
