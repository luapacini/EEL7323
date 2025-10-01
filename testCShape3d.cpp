/*
 * file: testCShape3d.cpp
 *
 * Descricao: Programa de teste para a Classe.
 *
 * Saida do programa:
 *
 * Volume do paralelograma: 730.17 
 * Volume do cone: 5.12707
 * Volume do cilindro: 20.3575
 *
 *
 * Autor: Rob McGregor
 * Data: ??/??/??
 * 
 * Ultima Alteracao: Eduardo Augusto Bezerra
 * Data da ultima alteracao: 29/05/2003
 *
 */

#include "CShape3d.cpp"
#include "CBox.cpp"
#include "CCone.cpp"
#include "CCylinder.cpp"

int main(){
	CShape3d* shape;

	// Um ponteiro para CShape3d assume a forma de um CBox
	//
	shape = new CBox(10.5f, 12.2f, 5.7f);
	cout << "Volume do paralelogramo: " << shape->volume() << endl;
	delete shape;

	// Um ponteiro para CShape3d assume a forma de um CCone
	//
	shape = new CCone(1.2f, 3.4f);
	cout << "Volume do cone: " << shape->volume() << endl;
	delete shape;

	// Um ponteiro para CShape3d assume a forma de um CCylinder
	//
	shape = new CCylinder(1.2f, 4.5f);
	cout << "Volume do cilindro: " << shape->volume() << endl;
	delete shape;

	return 0;
}

