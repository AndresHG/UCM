#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <iosfwd>
#include "TreeMap.h"

using namespace std;


void mostrar(const TreeMap<string, int> tree, string salida) {

	stringstream ss;
	TreeMap<string, int>::ConstIterator it = tree.cbegin();

	while (it != tree.cend()) {
		ss.str("");
		ss << it.value();
		string val = ss.str();

		salida += it.key() + " " + val + "\n";
		it.next();
	}

	cout << salida;
}

TreeMap<string, int> procesa(string &salida, int n) {
	
	TreeMap<string, int> tree;
	stringstream ss;
	stringstream ss1;
	stringstream ss2;

	for (int i = 0; i < n; i++) {

		ss.str("");
		ss1.str("");
		ss2.str("");

		ss << i + 1;
		string cont = ss.str();
		string origen, destino;
		int cantidad;

		cin >> origen >> destino >> cantidad;
		ss1 << cantidad;
		string cant = ss1.str();

		if (origen != "*" && !tree.contains(origen)) {
			tree.insert(origen, 0);
			if (!tree.contains(destino))
				tree.insert(destino, 0);
			salida += "op " + cont + ": le faltan " + cant + " euros \n";
		}
		else if (origen == "*" && !tree.contains(destino)) {
			tree.insert(destino, cantidad);
		}
		else if (origen == "*" && tree.contains(destino)) {
			tree.insert(destino, tree.at(destino) + cantidad);
		}
		else {
			if (tree.at(origen) - cantidad < 0) {
				ss2 << cantidad - tree.at(origen);
				if (!tree.contains(destino))
					tree.insert(destino, 0);
				string cant = ss2.str();
				salida += "op " + cont + ": le faltan " + cant + " euros \n";
			}
			else {
				if (!tree.contains(destino)) {
					tree.insert(destino, cantidad);
					tree.insert(origen, tree.at(origen) - cantidad);
				}
				else {
					tree.insert(origen, tree.at(origen) - cantidad);
					tree.insert(destino, tree.at(destino) + cantidad);
				}
			}
		}
	}
	return tree;
}


int main() {

	int casos;
	cin >> casos;

	for (int i = 0; i < casos; i++) {
		int n;
		cin >> n;
		string salida = "";
		TreeMap <string, int> tree = procesa(salida, n);
		mostrar(tree, salida);
	}

	system("PAUSE");
    return 0;
}

