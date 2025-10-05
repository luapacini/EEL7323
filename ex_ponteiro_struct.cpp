#include <iostream>
using namespace std;

typedef struct {
   int largura;
   int altura;
   unsigned *bits;
} Image;

void main() {
   Image pic1;
   Image *pImage = &pic1;
   pic1.largura = 100;

   cout << "pic1.largura == " << pic1.largura << endl;
   cout << "pImage->largura == " << pImage->largura << endl;
   cout << "(*pImage).largura == " << (*pImage).largura << endl;
   cout << "(&pic1)->largura == " << (&pic1)->largura << endl;

   // -> e' o operador ponteiro para membro de struct, class, union

   // Quais as saidas apos a execucao da instrucao abaixo?

   (*pImage).largura = 50;

   cout << "pic1.largura == " << pic1.largura << endl;
   cout << "pImage->largura == " << pImage->largura << endl;
   cout << "(*pImage).largura == " << (*pImage).largura << endl;
   cout << "(&pic1)->largura == " << (&pic1)->largura << endl;
} 