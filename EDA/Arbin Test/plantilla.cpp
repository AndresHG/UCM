#include <iostream>
#include <sstream>
#include <cstdlib>

#include "Arbin.h"

using namespace std;

string vertical(string a, string b);
string horizontal(string a, string b);

string metodo(const Arbin<string> &a) {

	string fin = "";
	if (!a.esVacio()) {
		
		if (a.raiz()[0] == 'V')
			fin = vertical(metodo(a.hijoIz()), metodo(a.hijoDr()));
		else if (a.raiz()[0] == 'H')
			fin = horizontal(metodo(a.hijoIz()), metodo(a.hijoDr()));
		else
			fin = a.raiz();
	}
	return fin;
}


string vertical(string a, string b) {

	size_t find = a.find('X');
	int ah, av, bh, bv;

	ah = atoi(a.substr(0, find).c_str());
	av = atoi(a.substr(find+1).c_str());

	find = b.find('X');
	bh = atoi(b.substr(0, find).c_str());
	bv = atoi(b.substr(find + 1).c_str());

	if (ah < bh)
		ah = bh;
	av += bv;

	stringstream flujo;
	flujo << ah << 'X' << av;

	return flujo.str();
}


string horizontal(string a, string b) {

	size_t find = a.find('X');
	int ah, av, bh, bv;

	ah = atoi(a.substr(0, find).c_str());
	av = atoi(a.substr(find + 1).c_str());

	find = b.find('X');
	bh = atoi(b.substr(0, find).c_str());
	bv = atoi(b.substr(find + 1).c_str());

	if (av < bv)
		av = bv;
	ah += bh;

	stringstream flujo;
	flujo << ah << 'X' << av;

	return flujo.str();
}


// muestra un arbol en notacion prefija y usando 2 espacios por nivel
//   OJO: no vas a poder, modificando solo este codigo, resolver
//   el problema - necesitas:
//     - o pasar mas parametros 
//        un stringstream para que el hijo se vaya mostrando, 
//        y devolver un bool si realmente debia mostrarse
//     - o una funcion recursiva auxiliar 
//        para saber si una rama se debe o no mostrar
//        (mas sencillo y recomendado, aunque menos eficiente, porque
//        evalua nodos varias veces)
void pre(int prof, const Arbin<string> &a) {
    if ( ! a.esVacio()) {
		metodo(a);
    }
}

// lee un programa a un arbol
//    asume que actual == "BEGIN" en primera llamada
//    y que nodos BEGIN y LOOP se cierran con END (mientras que OP no)
Arbin<string> procesa(string actual) {
    Arbin<string> iz, dr;
    string siguiente;
    
    if (actual[0] == 'H' || actual[0] == 'V' || actual[0] == 'E') {
        while (cin >> siguiente) {
            if (siguiente == "END") {
                break;
            }
            
            // nodos LOOP y OP tienen una <ENE> detras
           /* string ene;
            cin >> ene;
            siguiente = siguiente + " " + ene;*/
            
            if (iz.esVacio()) {            
                iz = procesa(siguiente);
            } else if (dr.esVacio()) {
                dr = procesa(siguiente);
            } else {
                cerr << "ERROR : tercer hijo " + siguiente << endl;
            }
        }
    }
    return Arbin<string>(iz, actual, dr);
}

// TUS FUNCIONES AUXILIARES AQUI


int main() {
	int n;
    cin >> n;
    for (int i=0; i<n; i++) {
        string s;
        cin >> s;
        Arbin<string> a = procesa(s);
		cout << metodo(a) << endl;
        // TU CODIGO AQUI
    }

	system("PAUSE");
    return 0;
}


/*
typedef Arbin<string> A;

int main() {
	//Arbin<string> A;
	A prueba(A(A("2X4"), "HBOX", A("1X4")));
	cout << metodo(prueba) << endl;

	A prueba1(A("HBOX"));
	cout << metodo(prueba1) << endl;

	A prueba2("HBOX");
	cout << metodo(prueba2) << endl;

	A prueba3(A(A("3X4"), "HBOX", A("1X5")),
		"VBOX",
		A(A("4X5"), "VBOX", A("2X3")));
	cout << metodo(prueba3) << endl;

	A prueba4(A(A("3X4"), "HBOX", A("HBOX")),
		"VBOX",
		A(A("4X5"), "VBOX", A("HBOX")));
	cout << metodo(prueba4) << endl;

	A prueba5(A("6X5"),
		"VBOX",
		A(A("4X5"), "VBOX", A("2X3")));
	cout << metodo(prueba5) << endl;

	A prueba6(A("2X3"), "HBOX", A("3X4"));
	cout << metodo(prueba6) << endl;

	A prueba7(A("VBOX"),
		"VBOX",
		A(A("HBOX"), "VBOX", A("HBOX")));
	cout << metodo(prueba7) << endl;

	system("PAUSE");
	return 0;
}

*/