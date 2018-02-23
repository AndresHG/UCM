
#include <iostream>
#include <string>
using namespace std;

#include "Arbin.h"

/*

Preorder;
	Raiz
	Hijo izquierdo
	Hijo derecho
*/

Arbin<string> procesa(string actual) {
	Arbin<string> iz, dr;
	string siguiente;

	if (actual[0] != 'O') {
		while (cin >> siguiente) {
			if (siguiente == "END") {
				break;
			}

			// nodos LOOP y OP tienen una <ENE> detras
			string ene;
			cin >> ene;
			siguiente = siguiente + " " + ene;

			if (iz.esVacio()) {
				iz = procesa(siguiente);
			}
			else if (dr.esVacio()) {
				dr = procesa(siguiente);
			}
			else {
				cerr << "ERROR : tercer hijo " + siguiente << endl;
			}
		}
	}
	return Arbin<string>(iz, actual, dr);
}

bool coincidenAux(const Arbin<string> &a, const List<string> &pre, int &i) {

	if (a.esVacio()) {
		return true;
	}
	if (a.raiz() == pre.at(i)) {
		i++;
	}
	else {
		return false;
	}

	return coincidenAux(a.hijoIz(), pre, i) && coincidenAux(a.hijoDr(), pre, i);
}

bool coinciden(const Arbin<string> &a, const List<string> &pre){

	int i = 0;

	return coincidenAux(a, pre, i);
	
}



int main(){

	Arbin<string> a;
	Arbin<string> iz, dr, l, n;
	iz = Arbin<string>(Arbin<string>(l, "3", n), "2", Arbin<string>(l, "4", n));
	dr = Arbin<string>(l, "5", n);
	a= Arbin<string>(iz, "1", dr);

	List<string> lista;

	lista.push_back("1");
	lista.push_back("2");
	lista.push_back("3");
	//lista.push_back("2");
	lista.push_back("4");
	lista.push_back("5");

	if (coinciden(a, lista))
		cout << "Coinciden";
	else
		cout << "No coinciden";
	//cout << coinciden(a, lista) ? "COINCIDEN\n" : "NO COINCIDEN\n";
	cout << endl;
	system("pause");

	return 0;
}