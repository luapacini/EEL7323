#include <iostream>

using namespace std;

class alunos {
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